#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "dsalib/input_parser.h"

using namespace dsalib;

namespace {

std::string JoinPath(const std::string& dir, const std::string& name) {
    if (dir.empty() || dir[dir.size() - 1] == '/') {
        return dir + name;
    }
    return dir + "/" + name;
}

void WriteFile(const std::string& path, const std::vector<unsigned char>& data) {
    std::ofstream os(path.c_str(), std::ios::binary);
    os.write(reinterpret_cast<const char*>(&data[0]),
             static_cast<std::streamsize>(data.size()));
}

void AppendU32(std::vector<unsigned char>& out, uint32_t value) {
    for (int i = 0; i < 4; ++i) {
        out.push_back(static_cast<unsigned char>((value >> (8 * i)) & 255));
    }
}

void FinishRecord(std::vector<unsigned char>& out) {
    uint32_t check = InputParser::checksum(out, 0, out.size());
    AppendU32(out, check);
}

std::vector<unsigned char> StartRecord(unsigned char type) {
    std::vector<unsigned char> out;
    out.push_back('D');
    out.push_back('S');
    out.push_back('A');
    out.push_back('1');
    AppendU32(out, 1);
    out.push_back(type);
    return out;
}

std::vector<unsigned char> EncodeNestedGraph(const Graph& graph) {
    std::vector<unsigned char> out = StartRecord(InputParser::TYPE_NESTED);
    std::vector<unsigned char> payload = InputParser::encode_graph(graph);
    out.push_back(InputParser::TYPE_GRAPH);
    InputParser::append_varuint(out, payload.size());
    out.insert(out.end(), payload.begin(), payload.end());
    InputParser::append_varuint(out, 1);
    out.push_back(InputParser::TYPE_NESTED);
    out.push_back(InputParser::TYPE_ARRAY);
    std::vector<int> marker;
    marker.push_back(graph.size());
    marker.push_back(static_cast<int>(payload.size()));
    std::vector<unsigned char> child_payload = InputParser::encode_array(marker);
    InputParser::append_varuint(out, child_payload.size());
    out.insert(out.end(), child_payload.begin(), child_payload.end());
    InputParser::append_varuint(out, 0);
    FinishRecord(out);
    return out;
}

std::vector<unsigned char> EncodeKnapsackLikeInput() {
    std::vector<unsigned char> out = StartRecord(InputParser::TYPE_NESTED);
    out.push_back(42);
    std::vector<unsigned char> payload;
    const int weights[] = {2, 3, 4, 5, 9, 13};
    const int values[] = {3, 4, 8, 8, 10, 17};
    InputParser::append_varuint(payload, 6);
    InputParser::append_varuint(payload, 17);
    for (int i = 0; i < 6; ++i) {
        InputParser::append_varint(payload, weights[i]);
        InputParser::append_varint(payload, values[i]);
    }
    InputParser::append_varuint(out, payload.size());
    out.insert(out.end(), payload.begin(), payload.end());
    InputParser::append_varuint(out, 0);
    FinishRecord(out);
    return out;
}

TreeNode<int>* BuildBalancedTree(int lo, int hi) {
    if (lo > hi) {
        return NULL;
    }
    int mid = lo + (hi - lo) / 2;
    TreeNode<int>* node = new TreeNode<int>(mid);
    node->left = BuildBalancedTree(lo, mid - 1);
    node->right = BuildBalancedTree(mid + 1, hi);
    return node;
}

TreeNode<int>* BuildDeepTree(int depth) {
    TreeNode<int>* root = NULL;
    TreeNode<int>* tail = NULL;
    for (int i = 0; i < depth; ++i) {
        TreeNode<int>* node = new TreeNode<int>(i);
        if (!root) {
            root = node;
        } else {
            tail->right = node;
        }
        tail = node;
    }
    return root;
}

Graph BuildSmallGraph() {
    Graph graph(5, true);
    graph.add_edge(0, 1, 7);
    graph.add_edge(1, 2, 3);
    graph.add_edge(2, 3, 4);
    graph.add_edge(3, 4, 1);
    graph.add_edge(0, 4, 20);
    return graph;
}

Graph BuildLargeGraph() {
    Graph graph(100, true);
    for (int i = 0; i < 99; ++i) {
        graph.add_edge(i, i + 1, (i % 11) + 1);
    }
    for (int i = 0; i < 100; i += 5) {
        graph.add_edge(i, (i + 17) % 100, (i % 7) + 1);
    }
    return graph;
}

Graph BuildCyclicGraph() {
    Graph graph(8, false);
    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 2);
    graph.add_edge(2, 0, 2);
    graph.add_edge(2, 3, 5);
    graph.add_edge(3, 4, 1);
    graph.add_edge(4, 5, 1);
    graph.add_edge(5, 3, 1);
    graph.add_edge(6, 7, 9);
    return graph;
}

std::vector<int> SortedArray() {
    std::vector<int> values;
    for (int i = 0; i < 128; ++i) {
        values.push_back(i * 2 - 64);
    }
    return values;
}

std::vector<int> RandomishArray() {
    std::vector<int> values;
    uint32_t x = 0x12345678u;
    for (int i = 0; i < 128; ++i) {
        x = x * 1664525u + 1013904223u;
        values.push_back(static_cast<int>(x % 2001) - 1000);
    }
    return values;
}

void GenerateCorpus(const std::string& output_dir) {
    Graph small = BuildSmallGraph();
    Graph large = BuildLargeGraph();
    Graph cyclic = BuildCyclicGraph();
    TreeNode<int>* balanced = BuildBalancedTree(1, 31);
    TreeNode<int>* deep = BuildDeepTree(64);
    std::vector<int> list_values;
    for (int i = 0; i < 64; ++i) {
        list_values.push_back(i % 17);
    }

    WriteFile(JoinPath(output_dir, "graph_small.bin"),
              InputParser::encode_graph(small));
    WriteFile(JoinPath(output_dir, "graph_large.bin"),
              InputParser::encode_graph(large));
    WriteFile(JoinPath(output_dir, "graph_cyclic.bin"),
              InputParser::encode_graph(cyclic));
    WriteFile(JoinPath(output_dir, "tree_balanced.bin"),
              InputParser::encode_tree(balanced));
    WriteFile(JoinPath(output_dir, "tree_deep.bin"),
              InputParser::encode_tree(deep));
    WriteFile(JoinPath(output_dir, "array_sorted.bin"),
              InputParser::encode_array(SortedArray()));
    WriteFile(JoinPath(output_dir, "array_random.bin"),
              InputParser::encode_array(RandomishArray()));
    WriteFile(JoinPath(output_dir, "linked_list.bin"),
              InputParser::encode_linked_list(list_values));
    WriteFile(JoinPath(output_dir, "dp_knapsack.bin"),
              EncodeKnapsackLikeInput());
    WriteFile(JoinPath(output_dir, "nested_graph.bin"),
              EncodeNestedGraph(small));

    BinaryTree<int>::destroy(balanced);
    BinaryTree<int>::destroy(deep);
}

}  // namespace

int main(int argc, char** argv) {
    std::string output_dir = argc > 1 ? argv[1] : ".";
    GenerateCorpus(output_dir);
    std::cout << "generated dsalib binary fixtures in " << output_dir << "\n";
    return 0;
}
