/*
 *1.无序数组经sort函数排序，传指针给array_mid_serch函数（即二分查找），还传入了n（数组长度），want_findd（目标元素，为了区分传值的概念，有别于want_find变量。
 *2.利用数组长度n，我们取得刚开始数组的起始位置left和结束位置right，当left<=right时（也就是数组不为空时），进行如下算法
 *（1）当arr[mid]=want_find时，找到则返回1
 *（2）当arr[mid]<want_find时，说明目标元素在经由mid分割的右区间，故将区间起始位置left赋值为mid+1
 *（3）当arr[mid]>want_find时，说明目标元素在经由mid分割的左区间，故将区间结束位置right赋值为mid-1
 *3.若数组为空，即代表找不到，返回0
 *4.用answer接收返回值，并用if语句判断返回值相应进行输出

 * Part of Cosmos by OpenGenus Foundation
 *
 * bubble sort synopsis
 *
 * template<typename _Bidirectional_Iter, typename _Compare>
 * void
 * bubbleSort(_Bidirectional_Iter begin, _Bidirectional_Iter end, _Compare compare);
 *
 * template<typename _Bidirectional_Iter>
 * void
 * bubbleSort(_Bidirectional_Iter begin, _Bidirectional_Iter end);
 */

#include <functional>

template<typename _Bidirectional_Iter, typename _Compare>
void
bubbleSort(_Bidirectional_Iter begin, _Bidirectional_Iter end, _Compare compare)
{
    if (begin != end)
    {
        auto frontOfSorted = end;

        for (--frontOfSorted; frontOfSorted != begin; --frontOfSorted)
        {
            bool swapped{};
            for (auto j = begin; j != frontOfSorted; ++j)
            {
                auto nextOfJ = j;
                if (compare(*++nextOfJ, *j))
                {
                    std::iter_swap(nextOfJ, j);
                    swapped = true;
                }
            }
            if (swapped == false)
                break;
        }
    }
}

template<typename _Bidirectional_Iter>
void
bubbleSort(_Bidirectional_Iter begin, _Bidirectional_Iter end)
{
    using value_type = typename std::iterator_traits<_Bidirectional_Iter>::value_type;

    bubbleSort(begin, end, std::less<value_type>());
}
