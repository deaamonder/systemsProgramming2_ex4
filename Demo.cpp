/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

void renderTree(sf::RenderWindow& window, Node<Complex>* node, float x, float y, float xOffset, float yOffset, sf::Font& font) {
    if (node) {
        // Draw current node
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(x, y);
        window.draw(circle);

        // Draw node value
        sf::Text text;
        text.setFont(font);
        text.setString(node->get_value().to_string());
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 5, y + 5);
        window.draw(text);

        // Draw connections to children and recurse
        auto children = node->get_children();
        float nextXOffset = xOffset / 2.f;
        float nextX = x - xOffset / 2.f;
        float nextY = y + yOffset;
        for (auto child : children) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20)),
                sf::Vertex(sf::Vector2f(nextX + 20, nextY + 20))
            };
            window.draw(line, 2, sf::Lines);
            renderTree(window, child, nextX, nextY, nextXOffset, yOffset, font);
            nextX += xOffset;
        }
    }
}

/*
int main()
{

    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
/*
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    for (auto node : tree)
    {
        cout << node.get_value() << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << tree; // Should print the graph using GUI.

    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Demo");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        cout << "Error loading font" << endl;
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        renderTree(window, tree.get_root(), 400.f, 50.f, 200.f, 100.f, font);
        window.display();
    }

*/

//main with complex numbers
int main() {
    Node<Complex> root_node (Complex(1.1, 2.2));
    Tree<Complex> tree; // Binary tree that contains Complex numbers.
    tree.add_root(root_node);
    Node<Complex> n1 (Complex(1.2, 2.3));
    Node<Complex> n2 (Complex(1.3, 2.4));
    Node<Complex> n3 (Complex(1.4, 2.5));
    Node<Complex> n4 (Complex(1.5, 2.6));
    Node<Complex> n5 (Complex(1.6, 2.7));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1 + 2.2i
     *     /       \
     *    1.2 + 2.3i   1.3 + 2.4i
     *   /  \      /
     *  1.4 + 2.5i  1.5 + 2.6i  1.6 + 2.7i
     */

    cout << "pre-order:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << (*node)->get_value() << endl;
    } // prints: 1.1 + 2.2i, 1.2 + 2.3i, 1.4 + 2.5i, 1.5 + 2.6i, 1.3 + 2.4i, 1.6 + 2.7i

    cout << "post-order:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << (*node)->get_value() << endl;
    } // prints: 1.4 + 2.5i, 1.5 + 2.6i, 1.2 + 2.3i, 1.6 + 2.7i, 1.3 + 2.4i, 1.1 + 2.2i

    cout << "in-order:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << (*node)->get_value() << endl;
    } // prints: 1.4 + 2.5i, 1.2 + 2.3i, 1.5 + 2.6i, 1.1 + 2.2i, 1.6 + 2.7i, 1.3 + 2.4i

    cout << "BFS:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << (*node)->get_value() << endl;
    } // prints: 1.1 + 2.2i, 1.2 + 2.3i, 1.3 + 2.4i, 1.4 + 2.5i, 1.5 + 2.6i, 1.6 + 2.7i

    // cout << "Default (BFS) traversal:" << endl;
    // for (auto node : tree) {
    //     cout << (*node)->get_value() << endl;
    // } // same as BFS: 1.1 + 2.2i, 1.2 + 2.3i, 1.3 + 2.4i, 1.4 + 2.5i, 1.5 + 2.6i, 1.6 + 2.7i

    //cout << tree; // Should print the graph using GUI.

    Tree<Complex, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1 + 2.2i
     *     /      |     \
     *    1.2 + 2.3i   1.3 + 2.4i  1.4 + 2.5i
     *   /        |
     *  1.5 + 2.6i  1.6 + 2.7i
     */

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Demo");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        cout << "Error loading font" << endl;
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        renderTree(window, three_ary_tree.get_root(), 400.f, 50.f, 200.f, 100.f, font);
        window.display();
    }

    return 0;
}