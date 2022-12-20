#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>

template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= static_cast<int>(vector.size());
    for (int i = len-1; i >0 ; --i) {
        for (int j = 0; j <i ; ++j) {
            if (comp(vector[j+1],vector[j])){
                std::swap(vector[j+1],vector[j]);
            }
        }
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= static_cast<int>(vector.size());
    for (int i = 1; i <len ; ++i) {
        T temp=vector[i];
        int j=i;
        while (j>0){
            if (comp(temp,vector[j-1])){
                vector[j]=vector[j-1];
                --j;
            }else{
                break;
            }
        }
        vector[j]=temp;
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    // select the maximum and minimum elements in one iteration to reduce runtime.
    int len= static_cast<int>(vector.size());
    for (int i = 0; i <len/2 ; ++i) {
        int min_ind=i, max_ind=len-i-1;
        for (int j = i; j <len-i ; ++j) {
            if (comp(vector[j],vector[min_ind])) min_ind=j;
            if (comp(vector[max_ind],vector[j])) max_ind=j;
        }
        std::swap(vector[max_ind],vector[len-i-1]);
        if (min_ind==len-i-1) min_ind=max_ind;
        std::swap(vector[min_ind],vector[i]);
    }
}

template<typename T, typename Compare>
void merge(std::vector<T> &vector, int left, int mid, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    int l_len= mid-left+1;
    int r_len= right-mid;
    std::vector<T> le(l_len);
    std::vector<T> ri(r_len);
    for (int i = 0; i <l_len; ++i) le[i]=vector[left+i];
    for (int j = 0; j <r_len; ++j) ri[j]=vector[mid+1+j];
    int l_ind=0, r_ind=0, cur=left;
    while (l_ind<l_len && r_ind<r_len){
        if (comp(ri[r_ind],le[l_ind])) vector[cur]=ri[r_ind++];
        else vector[cur]=le[l_ind++];
        cur++;
    }
    while (l_ind<l_len){
        vector[cur]=le[l_ind++];
        cur++;
    }
    while(r_ind<r_len){
        vector[cur]=ri[r_ind++];
        cur++;
    }
}

template<typename T, typename Compare>
void merge_helper(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    if (left>=right) return;
    int mid=(left+right)/2;
    merge_helper(vector,left,mid,comp);
    merge_helper(vector,mid+1,right,comp);
    merge(vector,left,mid,right,comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= static_cast<int>(vector.size());
    merge_helper(vector,0,len-1,comp);
}

template<typename T, typename Compare>
int partition_extra(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= right-left+1;
    int l= 0, r= len-1;
    std::vector<T> assist(len);
    for (int i = 0; i <len ; ++i) {
        assist[i]=vector[left+i];
    }
    T pivot=assist[0];
    for (int j = 1; j <len ; ++j) {
        if (comp(assist[j],pivot)){
            vector[left+l]=assist[j];
            ++l;
        }else{
            vector[left+r]=assist[j];
            --r;
        }
    }
    vector[left+l]=pivot;
    return left+l;
}

template<typename T, typename Compare>
void quick_sort_helper_extra(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    int pivot_ind;
    if (left>=right) return;
    pivot_ind=partition_extra(vector, left, right, comp);
    quick_sort_helper_extra(vector,left,pivot_ind-1,comp);
    quick_sort_helper_extra(vector,pivot_ind+1,right,comp);
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= static_cast<int>(vector.size());
    quick_sort_helper_extra(vector,0, len-1,comp);
}

template<typename T, typename Compare>
int partition_inplace(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    int i=left+1, j=right;
    while (true){
        while (comp(vector[i],vector[left]) && i<right) ++i;
        while (!comp(vector[j],vector[left]) && j>left) --j;
        if(i<j) std::swap(vector[i],vector[j]);
        else break;
    }
    if(left!=j) std::swap(vector[j],vector[left]);
    return j;
}

template<typename T, typename Compare>
void quick_sort_helper_inplace(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    // TODO: implement
    if (left>=right) return;
    int pivot_ind=partition_inplace(vector, left, right, comp);
    quick_sort_helper_inplace(vector,left,pivot_ind-1,comp);
    quick_sort_helper_inplace(vector,pivot_ind+1,right,comp);
}

template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int len= static_cast<int>(vector.size());
    quick_sort_helper_inplace(vector,0, len-1,comp);
}
#endif //VE281P1_SORT_HPP