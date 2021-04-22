#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>

class Graph {
private:
    float** the_graph;
    int num_vertices;
    
public:
    Graph(int num_vertices) {
        this->num_vertices = num_vertices;
        
        the_graph = new float*[num_vertices];
        for (int i = 0; i < num_vertices; i++) {
            the_graph[i] = new float[num_vertices];
            for (int j = 0; j < num_vertices; j++) {
                the_graph[i][j] = 0.0;
            }
        }
    }
    
    ~Graph() {
        for (int i = 0; i < num_vertices; i++) {
            delete[] the_graph[i];
        }
        delete[] the_graph;
    }
    
    void insert_edge(int from, int to, int out_degree) {
        the_graph[to][from] = 1.0 / out_degree;
    }
    
    float get_weight(int from, int to) {
        return the_graph[from][to];
    }
    
    void print_graph() {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                std::cout << the_graph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

void matrix_multiply(Graph & graph, std::vector<float> & page_rank) {
    double sum;
    std::vector<float> new_page_rank;
    new_page_rank.resize(page_rank.size());
    
    for (int i = 0; i < page_rank.size(); i++) {
        sum = 0;
        for (int j = 0; j < page_rank.size(); j++) {
            sum += (graph.get_weight(i, j) * page_rank[j]);
        }
        new_page_rank[i] = sum;
    }
    
    page_rank = new_page_rank;
}

int main() {
    // GET LINKS AND ITERATION COUNTS
    int num_links;
    std::cin >> num_links;
    int num_iters;
    std::cin >> num_iters;
    
    
    // MAPPING URLS
    std::set<std::string> seen_urls;
    std::map<std::string, int> mapped_urls;
    std::vector<std::tuple<std::string, std::string>> links;
    
    std::string temp1, temp2;
    int url_count = 0;
    
    for (int i = 0; i < num_links; i++) {
        std::cin >> temp1;
        if (seen_urls.count(temp1) == 0) {
            mapped_urls.insert({temp1, url_count});
            seen_urls.insert(temp1);
            url_count++;
        }
        
        std::cin >> temp2;
        if (seen_urls.count(temp2) == 0) {
            mapped_urls.insert({temp2, url_count});
            seen_urls.insert(temp2);
            url_count++;
        }
        
        links.emplace_back(std::make_tuple(temp1, temp2));
    }
    
    
    // GETTING OUT_DEGREE'S
    std::vector<int> url_outdegree(url_count, 0);
    
    for (int i = 0; i < links.size(); i++) {
        url_outdegree[mapped_urls[std::get<0>(links[i])]]++;
    }
    
    
    // BUILDING GRAPH
    Graph graph(url_count);
    
    for (int i = 0; i < links.size(); i++) {
        graph.insert_edge(mapped_urls[std::get<0>(links[i])], mapped_urls[std::get<1>(links[i])], url_outdegree[mapped_urls[std::get<0>(links[i])]]);
    }
    
    
    // PAGE RANKING
    std::vector<float> page_rank(url_count, 1.0 / url_count);
    
    for (int i = 0; i < num_iters - 1; i++) {
        matrix_multiply(graph, page_rank);
    }
    
    // PRINT PAGE RANKS
    for (std::set<std::string>::iterator it = seen_urls.begin(); it != seen_urls.end(); it++) {
        printf("%hhd %.2f\n", *it->c_str(), page_rank[mapped_urls[*it]]);
    }
    
    return 0;
}
