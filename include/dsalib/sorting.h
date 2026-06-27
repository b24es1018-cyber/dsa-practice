#ifndef DSALIB_SORTING_H
#define DSALIB_SORTING_H

#include <cstddef>
#include <string>
#include <vector>

namespace dsalib {

class Sorting {
public:
    typedef bool (*Comparator)(int, int);

    struct StabilityReport {
        bool merge_sort_stable;
        bool quick_sort_stable;
        bool heap_sort_stable;
        bool counting_sort_stable;
        bool radix_sort_stable;
        std::string summary;
    };

    static bool ascending(int lhs, int rhs);
    static bool descending(int lhs, int rhs);

    static void merge_sort(std::vector<int>& values,
                           Comparator comp = Sorting::ascending);
    static void quick_sort(std::vector<int>& values,
                           Comparator comp = Sorting::ascending);
    static void heap_sort(std::vector<int>& values,
                          Comparator comp = Sorting::ascending);

    static std::vector<int> counting_sort(const std::vector<int>& values);
    static std::vector<int> radix_sort(const std::vector<int>& values);

    static std::vector<int> external_merge_sort(const std::vector<int>& values,
                                                std::size_t chunk_size,
                                                Comparator comp =
                                                    Sorting::ascending);

    static bool is_sorted(const std::vector<int>& values,
                          Comparator comp = Sorting::ascending);
    static StabilityReport stability_analysis();

private:
    static void merge_sort_range(std::vector<int>& values,
                                 std::vector<int>& buffer,
                                 std::size_t left,
                                 std::size_t right,
                                 Comparator comp);
    static void merge_ranges(std::vector<int>& values,
                             std::vector<int>& buffer,
                             std::size_t left,
                             std::size_t mid,
                             std::size_t right,
                             Comparator comp);
    static void quick_sort_range(std::vector<int>& values,
                                 int left,
                                 int right,
                                 Comparator comp);
    static int partition(std::vector<int>& values,
                         int left,
                         int right,
                         Comparator comp);
    static int median_of_three(std::vector<int>& values,
                               int left,
                               int right,
                               Comparator comp);
    static void sift_down(std::vector<int>& values,
                          std::size_t start,
                          std::size_t end,
                          Comparator comp);
    static std::vector<int> merge_two_sorted(const std::vector<int>& a,
                                             const std::vector<int>& b,
                                             Comparator comp);
    static std::vector<int> radix_non_negative(std::vector<int> values);
};

}  // namespace dsalib

#endif
