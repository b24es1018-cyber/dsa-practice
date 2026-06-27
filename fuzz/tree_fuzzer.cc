#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "dsalib/input_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    dsalib::TreeNode<int>* root = NULL;
    dsalib::TreeNode<int>* roundtrip = NULL;

    try {
        std::vector<unsigned char> bytes(data, data + size);
        dsalib::InputParser parser(bytes);
        root = parser.parse_tree();

        volatile int height = dsalib::BinaryTree<int>::height(root);
        volatile int diameter = dsalib::BinaryTree<int>::diameter(root);
        volatile std::size_t inorder = dsalib::BinaryTree<int>::inorder(root).size();
        volatile std::size_t preorder = dsalib::BinaryTree<int>::preorder(root).size();
        volatile std::size_t postorder = dsalib::BinaryTree<int>::postorder(root).size();
        volatile std::size_t level = dsalib::BinaryTree<int>::level_order(root).size();
        (void)height;
        (void)diameter;
        (void)inorder;
        (void)preorder;
        (void)postorder;
        (void)level;

        dsalib::BinaryTree<int>::mirror(root);
        std::string serialized = dsalib::BinaryTree<int>::serialize(root);
        roundtrip = dsalib::BinaryTree<int>::deserialize(serialized);

        std::vector<unsigned char> encoded = dsalib::InputParser::encode_tree(root);
        dsalib::InputParser second(encoded);
        dsalib::TreeNode<int>* encoded_roundtrip = second.parse_tree();
        dsalib::BinaryTree<int>::destroy(encoded_roundtrip);

        dsalib::BinaryTree<int>::flatten(root);
        volatile std::size_t flattened = dsalib::BinaryTree<int>::preorder(root).size();
        (void)flattened;
    } catch (...) {
    }

    dsalib::BinaryTree<int>::destroy(root);
    dsalib::BinaryTree<int>::destroy(roundtrip);
    return 0;
}
