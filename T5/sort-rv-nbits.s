# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros sp, s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)

    # El puntero está en t0
    lw      t2,0(t0)            # t2 = p[0]
    lw      t3,4(t0)            # t3 = p[1]
    li      t4,0                # t4 = p0_ones = 0
    li      t5,0                # t5 = p1_ones = 0
    li      t6,0                # t6 = i = 0

.count:
    li      t1,32               # tope ciclo for -> for (t6 = 0; t6 < t7 = 32; t6++)
    beq     t6,t1,.count_done   # La 2da condición del for, si t6 = t7 (i = 32), el ciclo termina 

    # Contar 1's en t2 = p[0]
    srl     a0,t2,t6            # a0 = t2 >> t6 (a0 = p[0] >> i) 
    andi    a0,a0,1             # a0 = a0 & 1
    add     t4,t4,a0            # t4 = t4 + a0 (p0_ones++) 

    # Contar 1's en t3 = p[1]
    srl     a1,t3,t6            # a1 = t3 >> t6 (a1 = p[1] >> i)
    andi    a1,a1,1             # a1 = a1 & 1
    add     t5,t5,a1            # t5 = t5 + a1 (p1_ones++)

    addi    t6,t6,1             # t6 = t6 + 1 (i++)
    j       .count

.count_done:
    # Comparar cantidad de 1's
    li      t1,0                # t1 = 0
    bge     t4,t5,.decision     # Si t4 >= t5 (p0_ones >= p1_ones => t1 = 0 y no se invierten)
    li      t1,1                # Si t4 < t5 (p0_ones < p1_ones => t1 = 1 y se deben invertir)

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   // Se restaura direccion de retorno
    addi    sp,sp,64    #   // Desapila registro de activacion
    ret			# }
