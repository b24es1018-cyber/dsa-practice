#include "dsalib/sorting.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>

namespace dsalib {

bool Sorting::ascending(int lhs, int rhs) {
    return lhs < rhs;
}

bool Sorting::descending(int lhs, int rhs) {
    return lhs > rhs;
}

void Sorting::merge_sort(std::vector<int>& values, Comparator comp) {
    if (values.size() < 2) {
        return;
    }
    std::vector<int> buffer(values.size());
    merge_sort_range(values, buffer, 0, values.size(), comp);
}

void Sorting::merge_sort_range(std::vector<int>& values,
                               std::vector<int>& buffer,
                               std::size_t left,
                               std::size_t right,
                               Comparator comp) {
    if (right - left <= 1) {
        return;
    }
    std::size_t mid = left + (right - left) / 2;
    merge_sort_range(values, buffer, left, mid, comp);
    merge_sort_range(values, buffer, mid, right, comp);
    merge_ranges(values, buffer, left, mid, right, comp);
}

void Sorting::merge_ranges(std::vector<int>& values,
                           std::vector<int>& buffer,
                           std::size_t left,
                           std::size_t mid,
                           std::size_t right,
                           Comparator comp) {
    std::size_t i = left;
    std::size_t j = mid;
    std::size_t k = left;
    while (i < mid && j < right) {
        if (comp(values[j], values[i])) {
            buffer[k++] = values[j++];
        } else {
            buffer[k++] = values[i++];
        }
    }
    while (i < mid) {
        buffer[k++] = values[i++];
    }
    while (j < right) {
        buffer[k++] = values[j++];
    }
    for (std::size_t p = left; p < right; ++p) {
        values[p] = buffer[p];
    }
}

void Sorting::quick_sort(std::vector<int>& values, Comparator comp) {
    if (values.size() < 2) {
        return;
    }
    quick_sort_range(values, 0, static_cast<int>(values.size() - 1), comp);
}

void Sorting::quick_sort_range(std::vector<int>& values,
                               int left,
                               int right,
                               Comparator comp) {
    while (left < right) {
        int pivot = partition(values, left, right, comp);
        if (pivot - left < right - pivot) {
            quick_sort_range(values, left, pivot - 1, comp);
            left = pivot + 1;
        } else {
            quick_sort_range(values, pivot + 1, right, comp);
            right = pivot - 1;
        }
    }
}

int Sorting::median_of_three(std::vector<int>& values,
                             int left,
                             int right,
                             Comparator comp) {
    int mid = left + (right - left) / 2;
    if (comp(values[mid], values[left])) {
        std::swap(values[left], values[mid]);
    }
    if (comp(values[right], values[left])) {
        std::swap(values[left], values[right]);
    }
    if (comp(values[right], values[mid])) {
        std::swap(values[mid], values[right]);
    }
    return mid;
}

int Sorting::partition(std::vector<int>& values,
                       int left,
                       int right,
                       Comparator comp) {
    int pivot_index = median_of_three(values, left, right, comp);
    int pivot_value = values[pivot_index];
    std::swap(values[pivot_index], values[right]);
    int store = left;
    for (int i = left; i < right; ++i) {
        if (comp(values[i], pivot_value)) {
            std::swap(values[i], values[store]);
            ++store;
        }
    }
    std::swap(values[store], values[right]);
    return store;
}

void Sorting::heap_sort(std::vector<int>& values, Comparator comp) {
    if (values.size() < 2) {
        return;
    }
    for (int start = static_cast<int>((values.size() - 2) / 2);
         start >= 0;
         --start) {
        sift_down(values, static_cast<std::size_t>(start), values.size(), comp);
    }
    for (std::size_t end = values.size() - 1; end > 0; --end) {
        std::swap(values[0], values[end]);
        sift_down(values, 0, end, comp);
    }
}

void Sorting::sift_down(std::vector<int>& values,
                        std::size_t start,
                        std::size_t end,
                        Comparator comp) {
    std::size_t root = start;
    while (true) {
        std::size_t child = root * 2 + 1;
        if (child >= end) {
            break;
        }
        if (child + 1 < end && comp(values[child], values[child + 1])) {
            ++child;
        }
        if (comp(values[root], values[child])) {
            std::swap(values[root], values[child]);
            root = child;
        } else {
            break;
        }
    }
}

std::vector<int> Sorting::counting_sort(const std::vector<int>& values) {
    if (values.empty()) {
        return values;
    }
    int min_value = values[0];
    int max_value = values[0];
    for (std::size_t i = 1; i < values.size(); ++i) {
        min_value = std::min(min_value, values[i]);
        max_value = std::max(max_value, values[i]);
    }
    long long range = static_cast<long long>(max_value) -
                      static_cast<long long>(min_value) + 1;
    if (range <= 0 ||
        range > static_cast<long long>(values.size()) * 64 + 1000000) {
        std::vector<int> fallback = values;
        merge_sort(fallback);
        return fallback;
    }
    std::vector<std::size_t> counts(static_cast<std::size_t>(range), 0);
    for (std::size_t i = 0; i < values.size(); ++i) {
        ++counts[static_cast<std::size_t>(values[i] - min_value)];
    }
    std::vector<int> result;
    result.reserve(values.size());
    for (std::size_t i = 0; i < counts.size(); ++i) {
        while (counts[i]-- > 0) {
            result.push_back(static_cast<int>(i) + min_value);
        }
    }
    return result;
}

std::vector<int> Sorting::radix_non_negative(std::vector<int> values) {
    if (values.empty()) {
        return values;
    }
    int max_value = *std::max_element(values.begin(), values.end());
    for (int exp = 1; max_value / exp > 0; exp *= 10) {
        std::vector<int> output(values.size());
        int count[10] = {0};
        for (std::size_t i = 0; i < values.size(); ++i) {
            ++count[(values[i] / exp) % 10];
        }
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i) {
            int digit = (values[i] / exp) % 10;
            output[--count[digit]] = values[i];
        }
        values.swap(output);
        if (exp > std::numeric_limits<int>::max() / 10) {
            break;
        }
    }
    return values;
}

std::vector<int> Sorting::radix_sort(const std::vector<int>& values) {
    std::vector<int> negatives;
    std::vector<int> non_negative;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] < 0) {
            negatives.push_back(-values[i]);
        } else {
            non_negative.push_back(values[i]);
        }
    }
    negatives = radix_non_negative(negatives);
    non_negative = radix_non_negative(non_negative);
    std::vector<int> result;
    result.reserve(values.size());
    for (std::vector<int>::reverse_iterator it = negatives.rbegin();
         it != negatives.rend();
         ++it) {
        result.push_back(-*it);
    }
    result.insert(result.end(), non_negative.begin(), non_negative.end());
    return result;
}

std::vector<int> Sorting::merge_two_sorted(const std::vector<int>& a,
                                           const std::vector<int>& b,
                                           Comparator comp) {
    std::vector<int> merged;
    merged.reserve(a.size() + b.size());
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < a.size() && j < b.size()) {
        if (comp(b[j], a[i])) {
            merged.push_back(b[j++]);
        } else {
            merged.push_back(a[i++]);
        }
    }
    merged.insert(merged.end(), a.begin() + static_cast<long>(i), a.end());
    merged.insert(merged.end(), b.begin() + static_cast<long>(j), b.end());
    return merged;
}

std::vector<int> Sorting::external_merge_sort(const std::vector<int>& values,
                                              std::size_t chunk_size,
                                              Comparator comp) {
    if (chunk_size == 0) {
        throw std::invalid_argument("chunk_size must be positive");
    }
    std::vector<std::vector<int> > runs;
    for (std::size_t i = 0; i < values.size(); i += chunk_size) {
        std::size_t end = std::min(values.size(), i + chunk_size);
        std::vector<int> run(values.begin() + static_cast<long>(i),
                             values.begin() + static_cast<long>(end));
        merge_sort(run, comp);
        runs.push_back(run);
    }
    if (runs.empty()) {
        return std::vector<int>();
    }
    while (runs.size() > 1) {
        std::vector<std::vector<int> > next;
        for (std::size_t i = 0; i < runs.size(); i += 2) {
            if (i + 1 == runs.size()) {
                next.push_back(runs[i]);
            } else {
                next.push_back(merge_two_sorted(runs[i], runs[i + 1], comp));
            }
        }
        runs.swap(next);
    }
    return runs[0];
}

bool Sorting::is_sorted(const std::vector<int>& values, Comparator comp) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (comp(values[i], values[i - 1])) {
            return false;
        }
    }
    return true;
}

Sorting::StabilityReport Sorting::stability_analysis() {
    StabilityReport report;
    report.merge_sort_stable = true;
    report.quick_sort_stable = false;
    report.heap_sort_stable = false;
    report.counting_sort_stable = true;
    report.radix_sort_stable = true;
    report.summary =
        "Merge, counting, and radix sort preserve equal-key order in this "
        "library; quick sort and heap sort intentionally trade stability for "
        "in-place partitioning and heap operations.";
    return report;
}

}  // namespace dsalib
