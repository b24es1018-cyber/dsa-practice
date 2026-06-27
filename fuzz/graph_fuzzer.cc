#include <cstddef>
#include <cstdint>
#include <vector>

#include "dsalib/input_parser.h"

namespace {

bool HasSmallNonNegativeWeights(const dsalib::Graph& graph) {
    for (int u = 0; u < graph.size(); ++u) {
        const std::vector<std::pair<int, int> >& edges = graph.neighbors(u);
        for (std::size_t i = 0; i < edges.size(); ++i) {
            if (edges[i].second < 0 || edges[i].second > 1000000) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    try {
        std::vector<unsigned char> bytes(data, data + size);
        dsalib::InputParser parser(bytes);
        dsalib::Graph graph = parser.parse_graph();

        if (graph.size() == 0) {
            return 0;
        }

        volatile std::size_t bfs_count = graph.bfs(0).size();
        volatile std::size_t dfs_count = graph.dfs(0).size();
        volatile bool bipartite = graph.is_bipartite();
        volatile std::size_t components = graph.connected_components().size();
        (void)bfs_count;
        (void)dfs_count;
        (void)bipartite;
        (void)components;

        if (graph.directed()) {
            volatile bool cycle = graph.has_cycle_directed();
            volatile std::size_t topo = graph.topological_sort().size();
            (void)cycle;
            (void)topo;
        } else {
            volatile bool cycle = graph.has_cycle_undirected();
            (void)cycle;
        }

        if (HasSmallNonNegativeWeights(graph)) {
            volatile std::size_t dijkstra_count = graph.dijkstra(0).size();
            (void)dijkstra_count;
        }

        volatile bool bellman_ok = graph.bellman_ford(0).first;
        (void)bellman_ok;
    } catch (...) {
    }

    return 0;
}
