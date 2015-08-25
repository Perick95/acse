/*
 * Andrea Di Biagio
 * Politecnico di Milano, 2007
 * 
 * axe_array.c
 * Formal Languages & Compilers Machine, 2007/2008
 * 
 */

#include "axe_array.h"
#include "axe_gencode.h"
#include "symbol_table.h"
#include "axe_utils.h"
#include "axe_errors.h"


void rotateArray(t_program_infos *program, t_axe_variable *array, t_axe_expression displacement, int dir) {
    
    /* variabili ciclo esterno */
    t_axe_label *condition_loop = newLabel(program);
    t_axe_label *end_loop = newLabel(program);
    int index_last; // posizione dell'ultimo elemento
    int disp;
    int size;
    
    /* variabili ciclo interno */
    int index;
    int data;
    t_axe_expression index_exp,data_exp;
    
    /************* LOGICA *****************/
    
    // carico la lunghezza dell'array come immediato
    size = gen_load_immediate(program,array->arraySize);
    
    // carico la lunghezza, in index_last, per poi togliere 1 ed ottenere indice ultima cella
    index_last = gen_load_immediate(program,array->arraySize);
    gen_subi_instruction(program,index_last,index_last,1);
    
    // last_exp ora contiene l'indice dell'ultima cella dell'array
    t_axe_expression last_exp = create_expression(index_last,REGISTER);
    
    // carico displacement (di quanto spostare tutti gli elementi)
    if(displacement.expression_type == IMMEDIATE) {
        disp = gen_load_immediate(program,displacement.value);
    } else {
        disp = getNewRegister(program);
        disp = gen_andb_instruction(program,disp,displacement.value,displacement.value,CG_DIRECT_ALL);
    }
    // genero exp per il displacement
    t_axe_expression disp_exp = create_expression(disp,REGISTER);


    /***** INZIO CICLO ESTERNO ***/
    
        // inizio ciclo esterno (conta displacement da valore attuale fino a 0, decrementando)
        assignLabel(program,condition_loop);
        
        // se il disp è 0<= FINISCO! e mando su end_loop
        gen_ble_instruction(program,end_loop,0);
        
        
        // salvo array[0], altrimenti andrebbe perso!
        t_axe_expression index_0 = create_expression(0,IMMEDIATE);
        int element_0 = loadArrayElement(program,array->ID,index_0);
        t_axe_expression element_0_exp = create_expression(element_0,REGISTER);

        // fisso index a 1 (elemento 0 è già stato memorizzato)
        index = gen_load_immediate(program,1);
        index_exp = create_expression(index,REGISTER);

        /***** CICLO INTERNO *******/
        
            t_axe_label *end = newLabel(program);
            
            // assegno la label per ritornare qua
            t_axe_label *condition = assignNewLabel(program);
            
            // carico il dato dall'index corrente
            data = loadArrayElement(program,array->ID,index_exp);
            data_exp = create_expression(data,REGISTER);
            
            // per copiare il dato array[index] ad array[index-1] (scalano tutti verso sx: shift rotate sx)
            gen_subi_instruction(program,index,index,1);
            
            // salvo data in array[index-1]
            storeArrayElement(program,array->ID,index_exp,data_exp);
            
            // aggiungo +2: +1 per avanzamento indice, +1 perchè ho fatto la subi per ottere index-1
            gen_addi_instruction(program,index,index,2);

            // valuto se index è arrivato alla dimensione dell'array, sottraggo:
            int result = getNewRegister(program);
            gen_sub_instruction(program,result,index,size,CG_DIRECT_ALL);
            
            // se result = size-index = 0, allora vado alla fine (index=size, ho finito!)
            gen_beq_instruction(program,end,0);
            
            // altrimenti, torno alla condizione
            gen_bt_instruction(program,condition,0);

            assignLabel(program,end);
        
        /***** FINE CICLO INTERNO *******/
        

        // metto quello che era il primo alla fine
        storeArrayElement(program,array->ID,last_exp,element_0_exp);

        
        // tolgo 1 al displacement, perchè un ciclo di spostamenti è fatto
        gen_subi_instruction(program,disp,disp,1);
        
        // torno alla condizione
        gen_bt_instruction(program,condition_loop,0);
    
    /***** FINE CICLO ESTERNO ***/
    
    assignLabel(program,end_loop);
    
}


void storeArrayElement(t_program_infos *program, char *ID
            , t_axe_expression index, t_axe_expression data)
{
   int address;
   
   address =  loadArrayAddress(program, ID, index);

   if (data.expression_type == REGISTER)
   {
      /* load the value indirectly into `mova_register' */
      gen_add_instruction(program, address, REG_0
               , data.value, CG_INDIRECT_DEST);
   }
   else
   {
      int imm_register;

      imm_register = gen_load_immediate(program, data.value);

      /* load the value indirectly into `load_register' */
      gen_add_instruction(program, address, REG_0
               ,imm_register, CG_INDIRECT_DEST);
   }
}

int loadArrayElement(t_program_infos *program
               , char *ID, t_axe_expression index)
{
   int load_register;
   int address;

   /* retrieve the address of the array slot */
   address = loadArrayAddress(program, ID, index);

   /* get a new register */
   load_register = getNewRegister(program);

   /* load the value into `load_register' */
   gen_add_instruction(program, load_register, REG_0
            , address, CG_INDIRECT_SOURCE);

   /* return the register ID that holds the required data */
   return load_register;
}

int loadArrayAddress(t_program_infos *program
            , char *ID, t_axe_expression index)
{
   int mova_register;
   t_axe_label *label;

   /* preconditions */
   if (program == NULL)
      notifyError(AXE_PROGRAM_NOT_INITIALIZED);

   if (ID == NULL)
      notifyError(AXE_VARIABLE_ID_UNSPECIFIED);
   
   /* retrieve the label associated with the given
   * identifier */
   label = getLabelFromVariableID(program, ID);
                     
   /* test if an error occurred */
   if (label == NULL)
      return REG_INVALID;

   /* get a new register */
   mova_register = getNewRegister(program);

   /* generate the MOVA instruction */
   gen_mova_instruction(program, mova_register, label, 0);

   if (index.expression_type == IMMEDIATE)
   {
      if (index.value != 0)
      {
         gen_addi_instruction (program, mova_register
                  , mova_register, index.value);
      }
   }
   else
   {
      assert(index.expression_type == REGISTER);

      /* We are making the following assumption:
      * the type can only be an INTEGER_TYPE */
      gen_add_instruction(program, mova_register, mova_register
               , index.value, CG_DIRECT_ALL);
   }

   /* return the identifier of the register that contains
    * the value of the array slot */
   return mova_register;
}
