#include <cstddef>
#include <cstdint>
#include <vector>

#include "dsalib/input_parser.h"

namespace {

std::vector<unsigned char> ToBytes(const uint8_t* data, size_t size) {
    return std::vector<unsigned char>(data, data + size);
}

void TryArray(dsalib::InputParser& parser,
              const std::vector<unsigned char>& bytes) {
    try {
        parser.reset(bytes);
        volatile std::size_t count = parser.parse_array().size();
        (void)count;
    } catch (...) {
    }
}

void TryLinkedList(dsalib::InputParser& parser,
                   const std::vector<unsigned char>& bytes) {
    try {
        parser.reset(bytes);
        dsalib::LinkedList<int> list = parser.parse_linked_list();
        volatile std::size_t count = list.size();
        (void)count;
    } catch (...) {
    }
}

void TryGraph(dsalib::InputParser& parser,
              const std::vector<unsigned char>& bytes) {
    try {
        parser.reset(bytes);
        dsalib::Graph graph = parser.parse_graph();
        volatile int count = graph.size();
        (void)count;
    } catch (...) {
    }
}

void TryTree(dsalib::InputParser& parser,
             const std::vector<unsigned char>& bytes) {
    dsalib::TreeNode<int>* root = NULL;
    try {
        parser.reset(bytes);
        root = parser.parse_tree();
        volatile int height = dsalib::BinaryTree<int>::height(root);
        (void)height;
    } catch (...) {
    }
    dsalib::BinaryTree<int>::destroy(root);
}

void TryNested(dsalib::InputParser& parser,
               const std::vector<unsigned char>& bytes) {
    try {
        parser.reset(bytes);
        dsalib::BinaryField field = parser.parse_nested();
        volatile std::size_t payload = field.payload.size();
        (void)payload;
    } catch (...) {
    }
}

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    static dsalib::InputParser parser;
    const std::vector<unsigned char> bytes = ToBytes(data, size);

    TryGraph(parser, bytes);
    TryTree(parser, bytes);
    TryArray(parser, bytes);
    TryLinkedList(parser, bytes);
    TryNested(parser, bytes);

    return 0;
}
