#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Node;
using umpnnll = std::unordered_map<std::string, std::shared_ptr<Node>>; 

struct Node
{
    std::string course;
    std::shared_ptr<Node> next;
    Node(std::string course, std::shared_ptr<Node> next=nullptr)
    : course(course), 
    next(next) {}
};

bool FindDependentCourse(const umpnnll &input, std::vector<std::string> &v_nodes, std::unordered_set<std::string> &m_nodes)
{
    bool ret = false;

    if(input.size() == m_nodes.size()) return true;

    auto nodes = input.find(v_nodes.back());
    if(nodes == input.end()) return ret;

    auto temp = nodes->second;
    while (temp)
    {
        auto next_course = temp->course;
        if(m_nodes.find(next_course) == m_nodes.end())
        {
            m_nodes.emplace(next_course);
            v_nodes.emplace_back(next_course);
            ret = FindDependentCourse(input, v_nodes, m_nodes);
            if(ret) break;
            v_nodes.pop_back();
            m_nodes.erase(m_nodes.find(next_course));
        }
        temp = temp->next;
    }
    
    return ret;
}

std::shared_ptr<Node> FindDependency(const umpnnll &input)
{
    std::shared_ptr<Node> ret = nullptr;
    if(input.empty()) return ret;

    auto input_size = input.size(); 

    std::vector<std::string> v_nodes;
    std::unordered_set<std::string> m_nodes;
    for(auto &iter : input) // go over each courses and find the dependencies
    {
        std::string course = iter.first;
        m_nodes.emplace(course); // maintain set to maintain course unique codes
        v_nodes.emplace_back(course); // maintain vector for preserving dependency chain
        if(FindDependentCourse(input, v_nodes, m_nodes)) break;
        v_nodes.pop_back();
        m_nodes.erase(m_nodes.find(course));
    }

    std::shared_ptr<Node> temp = nullptr; // convert vector to link-list
    for(auto &iter : v_nodes)
    {
        temp = std::make_shared<Node>(iter);
        temp->next = ret;
        ret = temp;
    }
    return ret;
}

void Display(std::shared_ptr<Node> node)
{
    if(node) std::cout<<"("<<node->course;
    else { std::cout<<"no ordering\n"; return;}
    node = node->next;
    while(node)
    {
        std::cout<<", "<<node->course<<"";
        node = node->next;
    }
    std::cout<<")\n";
}

int main()
{
    // test case 1:
    umpnnll input1;
    input1.emplace("CSC300", std::make_shared<Node>("CSC100", std::make_shared<Node>("CSC200")));
    input1.emplace("CSC200", std::make_shared<Node>("CSC100"));
    input1.emplace("CSC100", nullptr);
    auto dependency1 = FindDependency(input1);
    Display(dependency1);

    // test case 2:
    umpnnll input2;
    input2.emplace("CSC300", std::make_shared<Node>("CSC100", std::make_shared<Node>("CSC200")));
    input2.emplace("CSC200", nullptr);
    input2.emplace("CSC100", nullptr);
    auto dependency2 = FindDependency(input2);
    Display(dependency2);

    // test case 3:
    umpnnll input3;
    input3.emplace("CSC300", std::make_shared<Node>("CSC100", std::make_shared<Node>("CSC200")));
    input3.emplace("CSC200", std::make_shared<Node>("CSC300", std::make_shared<Node>("CSC100")));
    input3.emplace("CSC100", nullptr);
    auto dependency3 = FindDependency(input3);
    Display(dependency3);

    // test case 4:
    umpnnll input4;
    input4.emplace("CSC300", nullptr);
    input4.emplace("CSC200", nullptr);
    input4.emplace("CSC100", nullptr);
    auto dependency4 = FindDependency(input4);
    Display(dependency4);

    return 0;
}