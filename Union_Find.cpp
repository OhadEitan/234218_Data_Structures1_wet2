////
//// Created by eitan on 20/12/2022.
////
//
//#include "Union_Find.h"
//
//
//UF::UF(long long int value): size(value+1), current_size(value) {
//    //groups = new int*[s];
//    father = new long long int[value + 1];
//    sizes_arr = new long long int[value + 1];
//    for (long long i = 1; i < value + 1; i++)
//        makeSet(i);
//}
//
//UF::~UF()
//{
//    //delete[] groups;
//    delete[] father;
//    delete[] sizes_arr;
//}
//
//int UF::find(long long int value) {
//    long long int find_rout = value;
//    //// first finding the rout
//    while(father[find_rout]) {
//        find_rout = father[find_rout];
//    }
//    /// path compress
//    while(father[value])
//    {
//        long long int before_rout  = value;
//         value = father[value];
//         father[before_rout] = find_rout;
//    }
//    return find_rout;
//}
//
//void UF::union_function(long long int set1, long long int  set2) {
//    long long int a = find(set1);
//    long long int b = find(set2);
//    if(a == b)
//    {
//        ////do nothing
//    }
//    if(sizes_arr[a] >= sizes_arr[b] )
//    {
//        father[b] = a;
//        sizes_arr[a] += sizes_arr[b];
//        sizes_arr[b] = 0;
//        current_size--;
//
//    }
//    else {
//        father[a] = b;
//        sizes_arr[b] += sizes_arr[a];
//        sizes_arr[a] = 0;
//        current_size--;
//        return;
//    }
//}
//
//
//
//void UF::makeSet(long long int value) {
//    //groups[i] = new int;
//    //*(groups[i]) = i;
//    father[value] = 0;
//    sizes_arr[value] = 1;
//}
//
//void UF::print_func() {
//
//}
