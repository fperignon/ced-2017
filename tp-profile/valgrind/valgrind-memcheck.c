/*
 *
 *  File:       valgrind-memcheck.c
 *  Brief:      Testing types of memleaks reported by valgrind-memcheck
 *
 *  Author:     Aleksander Morgado <aleksander@es.gnu.org>
 *  Date:       Wed Jan 27 13:24:57 2010
 *
 *
 *  Compile with:
 *   $> gcc -o valgrind-memcheck valgrind-memcheck.c
 *
 *  Test with:
 *   $> valgrind --leak-check=full --show-reachable=yes ./valgrind-memcheck N
 *
 *
 *  Check section 4.2.7 (Memory Leak Detection) in the Valgrind Manual:
 *  http://valgrind.org/docs/manual/mc-manual.html
 *
 */



/*
 * Copyright (C) 2010 Aleksander Morgado
 * This code is in the public domain
 */



#include <stdio.h>
#include <malloc.h>
#include <string.h>


/*
 * Note: global pointers are used in order to easily show 'still reachable
 * leaks, this is, those were the pointer to the heap block is still available
 * when program exits
 */
static void *rrr;
static void **p_rrr;


static void
__header(const char *title)
{
    printf("-----------------------------------\n"
           "%s\n"
           "-----------------------------------\n",
           title);
}



/*
 * This case is listed as (1) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (1)  RRR ------------> BBB                    DR
 */
static void
__case_1(void)
{
    __header("Testing valgrind-memcheck for Directly Reachable memleak "
             "in BBB");

    /*
     * Memory allocation in heap duplicating a string. This is the BBB heap
     *  block. We now have RRR ---> BBB
     */
    rrr = strdup("bbb");

    /* Oops, we don't free the BBB block.
     *
     * - The BBB heap block will be marked as Directly Reachable by valgrind,
     *    and will be shown as "Still Reachable" in the output report
     */
}

/*
 * This case is listed as (2) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (2)  RRR ---> AAA ---> BBB    DR              IR
 */
static void
__case_2(void)
{
    __header("Testing valgrind-memcheck for Indirectly Reachable memleak "
             "in BBB (and Directly Reachable in AAA)");

    /*
     * Memory allocation in heap for a pointer. This is the AAA heap block
     *  We now have RRR ---> AAA
     */
    p_rrr = malloc(sizeof(void **));

    /*
     * Memory allocation in heap for a string. This is the BBB heap block
     *  We now have RRR ---> AAA ---> BBB
     */
    *p_rrr = strdup("bbb");

    /* Oops, we don't free neither the AAA block nor the BBB block.
     *
     * - The AAA heap block will be marked as Directly Reachable by valgrind,
     *    and will be shown as "Still Reachable" in the output report
     *
     * - The BBB heap block will be marked as Indirectly Reachable by valgrind,
     *    and will be shown as "Still Reachable" in the output report
     *
     */
}



/*
 * This case is listed as (3) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (3)  RRR               BBB                    DL
 */
static void
__case_3(void)
{
    __header("Testing valgrind-memcheck for Directly Lost memleak "
             "in BBB");

    /*
     * Memory allocation in heap duplicating a string. This is the BBB heap
     *  block. We now have RRR ---> BBB
     */
    rrr = strdup("bbb");

    /* Oops, we don't free the BBB block, and we also re-use the RRR pointer
     *
     * - The BBB heap block will be marked as Directly Lost by valgrind,
     *    and will be shown as "Definitely Lost" in the output report
     */
    rrr = NULL;
}



/*
 * This case is listed as (4) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (4)  RRR      AAA ---> BBB    DL              IL
 */
static void
__case_4(void)
{
    __header("Testing valgrind-memcheck for Indirectly Lost memleak "
             "in BBB (and Directly Lost in AAA)");

    /*
     * Memory allocation in heap for a pointer. This is the AAA heap block
     *  We now have RRR ---> AAA
     */
    p_rrr = malloc(sizeof(void **));

    /*
     * Memory allocation in heap for a string. This is the BBB heap block
     *  We now have RRR ---> AAA ---> BBB
     */
    *p_rrr = strdup("bbb");

    /* Oops, we don't free neither the AAA block nor the BBB block, and
     *  we also re-use the RRR pointer pointing to AAA.
     *
     * - The AAA heap block will be marked as Directly Lost by valgrind,
     *    and will be shown as "Definitely Lost" in the output report
     *
     * - The BBB heap block will be marked as Indirectly Lost by valgrind,
     *    and will be shown as "Definitely Lost" in the output report
     *
     */
    p_rrr = NULL;
}




/*
 * This case is listed as (5) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (5)  RRR ------?-----> BBB                    (y)DR, (n)DL
 */
static void
__case_5(void)
{
    __header("Testing valgrind-memcheck for Possibly Lost "
             "memleak in BBB with an interior pointer to BBB");

    /* Store in RRR the address of the newly allocated BBB block */
    rrr = strdup("bbb");

    /* We setup a valid interior-pointer to 1 byte inside BBB
     * (start-pointer to BBB is lost)
     */
    rrr = ((char *)rrr)+1;

    /* Oops, we don't free the BBB block, and we also re-use the pointer,
     *  but we have an interior pointer
     *
     * - The BBB heap block could be either Directly Reachable (if the
     *   interior pointer is a real one), or Directly Lost (if the
     *   interior pointer is not real, this is, a chunk of memory which
     *   happened to have the address of a valid internal pointer).
     *   In any case, Valgrind cannot decide between the two possibilities
     *   so the memleak will be shown as "Possibly Lost" in the output report
     */
}


/*
 * This case is listed as (6) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (6)  RRR ---> AAA -?-> BBB    DR              (y)IR, (n)DL
 */
static void
__case_6(void)
{
    __header("Testing valgrind-memcheck for Possibly Lost "
             "memleak in BBB, with an interior pointer to somewhere "
             "in BBB (and Directly Reachable memleak in AAA)");

    /* Store in RRR the address of the newly allocated AAA block */
    p_rrr = malloc(sizeof(void **));

    /* Store in AAA the address of the newly allocated BBB block */
    *p_rrr = strdup("bbb");

    /* We setup a valid interior-pointer to 1 byte inside BBB
     * (start-pointer to BBB is lost)
     */
    *p_rrr = ((char *)(*p_rrr))+1;

    /* Oops, we don't free neither the AAA block nor the BBB block, and we reused
     * the pointer in AAA, but we have an interior pointer to BBB.
     *
     * - The AAA heap block will be marked as Directly Reachable by valgrind,
     *    and will be shown as "Still Reachable" in the output report
     *
     * - The BBB heap block could be either Indirectly Reachable (if the
     *   interior pointer is a real one), or Directly Lost (if the
     *   interior pointer is not real, this is, a chunk of memory which
     *   happened to have the address of a valid internal pointer).
     *   In any case, Valgrind cannot decide between the two possibilities
     *   so the memleak will be shown as "Possibly Lost" in the output report
     *
     */
}



/*
 * This case is listed as (7) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (7)  RRR -?-> AAA ---> BBB    (y)DR, (n)DL    (y)IR, (n)IL
 */
static void
__case_7(void)
{
    __header("Testing valgrind-memcheck for Possibly Lost "
             "memleaks in AAA and BBB, with an interior pointer to somewhere "
             "in AAA");

    /*
     * Memory allocation in heap for a pointer. This is the AAA heap block
     *  We now have RRR ---> AAA
     */
    p_rrr = malloc(sizeof(void **));

    /*
     * Memory allocation in heap for a string. This is the BBB heap block
     *  We now have RRR ---> AAA ---> BBB
     */
    *p_rrr = strdup("bbb");

    /* We setup a valid interior pointer to 1 byte inside AAA */
    p_rrr = (void **)((char *)p_rrr + 1);


    /* Oops, we don't free neither the AAA block nor the BBB block, and we reused
     * the pointer RRR, but we have an interior pointer to AAA.
     *
     * - The AAA heap block could be either Directly Reachable (if the
     *   interior pointer is a real one), or Directly Lost (if the
     *   interior pointer is not real, this is, a chunk of memory which
     *   happened to have the address of a valid internal pointer).
     *   In any case, Valgrind cannot decide between the two possibilities
     *   so the memleak will be shown as "Possibly Lost" in the output report
     *
     * - The BBB block could be Inderectly Reachable (if AAA was Directly
     *   Reachable) or Indirectly Lost (if AAA was Directly Lost).
     *   Valgrind cannot decide between the two possibilities so the memleak
     *   will be shown as "Possibly Lost" in the output report
     *
     */
}


/*
 * This case is listed as (8) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (8)  RRR -?-> AAA -?-> BBB    (y)DR, (n)DL    (y,y)IR, (n,y)IL, (_,n)DL
 */
static void
__case_8(void)
{
    __header("Testing valgrind-memcheck for Possibly Lost "
             "memleaks in AAA and BBB, with an interior pointer to somewhere "
             "in AAA and an interior pointer to somewhere in BBB");

    /*
     * Memory allocation in heap for a pointer. This is the AAA heap block
     *  We now have RRR ---> AAA
     */
    p_rrr = malloc(sizeof(void **));

    /*
     * Memory allocation in heap for a string. This is the BBB heap block
     *  We now have RRR ---> AAA ---> BBB
     */
    *p_rrr = strdup("bbb");


    /* We setup in AAA, a valid interior pointer to 1 byte inside
     *  BBB (start-pointer to BBB is lost) */
    *p_rrr = ((char *)(*p_rrr))+1;

    /* We setup in RRR, a valid interior pointer to 1 byte inside
     *  AAA (start-pointer to AAA is lost) */
    p_rrr = (void **)(((char *)(p_rrr))+1);


    /* Oops, we don't free neither the AAA block nor the BBB block, and we reused
     * the pointers RRR and AAA, but we have an interior pointer to AAA and
     * another interior pointer to BBB
     *
     * - The AAA heap block could be either Directly Reachable (if the
     *   First interior pointer is a real one), or Directly Lost (if the
     *   First interior pointer is not real, this is, a chunk of memory which
     *   happened to have the address of a valid internal pointer).
     *   In any case, Valgrind cannot decide between the two possibilities
     *   so the memleak will be shown as "Possibly Lost" in the output report
     *
     * - The BBB block could be Inderectly Reachable (if AAA was Directly
     *   Reachable) and Second interior pointer is valid; or Indirectly Lost
     *   (if AAA was Directly Reachable and Second interior pointer is
     *   valid; or Directly Lost (if Second pointer is NOT valid, whatever AAA
     *   was).
     *   Valgrind cannot decide between the two possibilities so the memleak
     *   will be shown as "Possibly Lost" in the output report
     *
     */
}


/*
 * This case is listed as (9) in valgrind documentation.
 *
 *      Pointer chain            AAA Category    BBB Category
 *      ----------------------   ------------    ------------
 * (9)  RRR      AAA -?-> BBB    DL              (y)IL, (n)DL
 */
static void
__case_9(void)
{
    __header("Testing valgrind-memcheck for Possibly Lost "
             "memleak in BBB, with an interior pointer to somewhere "
             "in BBB (and Directly Lost memleak in AAA)");

    /*
     * Memory allocation in heap for a pointer. This is the AAA heap block
     *  We now have RRR ---> AAA
     */
    p_rrr = malloc(sizeof(void **));

    /*
     * Memory allocation in heap for a string. This is the BBB heap block
     *  We now have RRR ---> AAA ---> BBB
     */
    *p_rrr = strdup("bbb");

    /* We setup a valid interior pointer to 1 byte inside BBB */
    *p_rrr = ((char *)(*p_rrr)+1);

    /* And we reset the RRR pointer */
    p_rrr = NULL;


    /* Oops, we don't free neither the AAA block nor the BBB block, and we
     * reused the RRR pointer and the pointer in AAA, but we have an
     * interior pointer to BBB.
     *
     * - The AAA heap block will be marked as Directly Lost by valgrind,
     *    and will be shown as "Definitely Lost" in the output report
     *
     * - The BBB heap block could be either Indirectly Lost (if the
     *   interior pointer is a real one), or Directly Lost (if the
     *   interior pointer is not real, this is, a chunk of memory which
     *   happened to have the address of a valid internal pointer).
     *   In any case, Valgrind cannot decide between the two possibilities
     *   so the memleak will be shown as "Possibly Lost" in the output report
     *
     */
}



static void
__show_usage(const char *program_name)
{
    printf(" Usage: %s <1-9>\n\n",
           program_name);
}


int main(int argc, char **argv)
{
    int valgrind_case = 0;

    if(argc == 2)
        valgrind_case = atoi(argv[1]);

    switch (valgrind_case)
    {
        case 1: __case_1(); break;
        case 2: __case_2(); break;
        case 3: __case_3(); break;
        case 4: __case_4(); break;
        case 5: __case_5(); break;
        case 6: __case_6(); break;
        case 7: __case_7(); break;
        case 8: __case_8(); break;
        case 9: __case_9(); break;
        default:
            __show_usage(argv[0]);
            return -1;
    }
    return 0;
}

/* End of valgrind-memcheck.c */
