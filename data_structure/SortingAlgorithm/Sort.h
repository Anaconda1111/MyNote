//
// Created by xcs on 2021-05-11.
//

#ifndef SORTINGALGORITHM__SORT_H_
#define SORTINGALGORITHM__SORT_H_
#define ElementType int
//插入排序：
void InsertionSort(ElementType A[],int n);

//希尔排序：
void ShellSort(ElementType A[],int N);

//堆排序：
void PercDown(ElementType A[],int i,int N);
void HeapSort(ElementType A[],int N);

//归并排序：
void Merge(ElementType A[],ElementType temp[],int L_StartPosition,int R_StartPosition,int RightEnd);
void Msort(ElementType A[],ElementType temp[],int Left,int Right);
void MergeSort(ElementType A[],int Num);

//快速排序：
ElementType Median3(ElementType A[],int Left,int Right);
void QSort(ElementType A[],int Left,int Right);
void QuickSort(ElementType A[],int N);

//桶排序：
void BucketSort(ElementType A[],int N);
#endif//SORTINGALGORITHM__SORT_H_
