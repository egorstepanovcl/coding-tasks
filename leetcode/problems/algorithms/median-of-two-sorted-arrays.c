// Решил: Егор Степанов <https://github.com/egorstepanovcl>

// Название: 4. Медиана двух отсортированных массивов (4. Median of Two Sorted Arrays)

// Задача:
// Если даны два отсортированных массива nums1 и nums2 размером m и n соответственно, верните медиану двух отсортированных массивов.
// Общая сложность времени выполнения должна быть O(log (m+n)).

// Пример 1:
// Вход: nums1 = [1,3], nums2 = [2]
// Выход: 2.00000
// Пояснение: объединенный массив = [1,2,3] и медиана равна 2.

// Пример 2:
// Вход: nums1 = [1,2], nums2 = [3,4]
// Выход: 2.50000
// Пояснение: объединенный массив = [1,2,3,4] и медиана равна (2 + 3) / 2 = 2,5.

// Ограничения:
// nums1.length == m
// nums2.length == n
// 0 <= m <= 1000
// 0 <= n <= 1000
// 1 <= m + n <= 2000
// -10⁶ <= nums1[i], nums2[i] <= 10⁶

#include <limits.h>

// Функция для нахождения медианы двух отсортированных массивов
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Убедимся, что nums1 является меньшим массивом
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    
    int m = nums1Size;
    int n = nums2Size;
    int half_len = (m + n + 1) / 2;
    int imin = 0, imax = m, max_of_left, min_of_right;
    
    while (imin <= imax) {
        int i = (imin + imax) / 2;
        int j = half_len - i;
        
        if (i < m && nums2[j-1] > nums1[i]) {
            // i слишком маленькое, увеличиваем его
            imin = i + 1;
        } else if (i > 0 && nums1[i-1] > nums2[j]) {
            // i слишком большое, уменьшаем его
            imax = i - 1;
        } else {
            // i идеально
            if (i == 0) { max_of_left = nums2[j-1]; }
            else if (j == 0) { max_of_left = nums1[i-1]; }
            else { max_of_left = (nums1[i-1] > nums2[j-1]) ? nums1[i-1] : nums2[j-1]; }
            
            if ((m + n) % 2 == 1) {
                return max_of_left;
            }
            
            if (i == m) { min_of_right = nums2[j]; }
            else if (j == n) { min_of_right = nums1[i]; }
            else { min_of_right = (nums1[i] < nums2[j]) ? nums1[i] : nums2[j]; }
            
            return (max_of_left + min_of_right) / 2.0;
        }
    }
    
    return 0.0;
}