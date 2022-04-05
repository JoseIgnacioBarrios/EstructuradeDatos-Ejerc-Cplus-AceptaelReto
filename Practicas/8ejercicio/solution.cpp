/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
/*
* MUY IMPORTANTE: Para realizar este ejercicio solo podéis
* modificar el código contenido entre las etiquetas <answer>
* y </answer>. Toda modificación fuera de esas etiquetas está
* prohibida, pues no se tendrá en cuenta para la corrección.
*
* Tampoco esta permitido modificar las líneas que contienen
* las etiquetas <answer> y </answer>, obviamente :-)
*/

//@ <answer>
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Jorge Valmaseda Plasencia
  Componente 2: Jose Ignacio Barrios Oros
*/
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <vector>
#include <stack>


// TAD Conjunto implementado mediante árboles binarios de búsqueda.
template <typename T> class SetTree {
public:
  SetTree() : root_node(nullptr), num_elems(0) {}
  SetTree(const SetTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  ~SetTree() { delete_nodes(root_node); }

  void insert(const T &elem) {
    auto [new_root, inserted] = insert(root_node, elem);
    root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const T &elem) const { return search(root_node, elem); }

  void erase(const T &elem) {
    auto [new_root, removed] = erase(root_node, elem);
    root_node = new_root;
    if (removed) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  SetTree &operator=(const SetTree &other) {
    if (this != &other) {
      num_elems = other.num_elems;
      delete_nodes(root_node);
      root_node = copy_nodes(other.root_node);
    }
    return *this;
  }

  void display(std::ostream &out) const {
    out << "{";
    display(root_node, out);
    out << "}";
  }

private:
  struct Node {
    T elem;
    Node *left, *right;

    Node(Node *left, const T &elem, Node *right)
        : left(left), elem(elem), right(right) {}
  };

  Node *root_node;
  int num_elems;

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->elem,
                      copy_nodes(node->right));
    }
  }

  static void delete_nodes(const Node *node) {
    if (node != nullptr) {
      delete_nodes(node->left);
      delete_nodes(node->right);
      delete node;
    }
  }

  static std::pair<Node *, bool> insert(Node *root, const T &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (elem < root->elem) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (root->elem < elem) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  static bool search(const Node *root, const T &elem) {
    if (root == nullptr) {
      return false;
    } else if (elem == root->elem) {
      return true;
    } else if (elem < root->elem) {
      return search(root->left, elem);
    } else {
      return search(root->right, elem);
    }
  }

  static std::pair<Node *, bool> erase(Node *root, const T &elem) {
    if (root == nullptr) {
      return {root, false};
    } else if (elem < root->elem) {
      auto [new_root_left, erased] = erase(root->left, elem);
      root->left = new_root_left;
      return {root, erased};
    } else if (root->elem < elem) {
      auto [new_root_right, erased] = erase(root->right, elem);
      root->right = new_root_right;
      return {root, erased};
    } else {
      return {remove_root(root), true};
    }
  }

  static Node *remove_root(Node *root) {
    Node *left_child = root->left, *right_child = root->right;
    delete root;
    if (left_child == nullptr && right_child == nullptr) {
      return nullptr;
    } else if (left_child == nullptr) {
      return right_child;
    } else if (right_child == nullptr) {
      return left_child;
    } else {
      auto [lowest, new_right_root] = remove_lowest(right_child);
      lowest->left = left_child;
      lowest->right = new_right_root;
      return lowest;
    }
  }

  static std::pair<Node *, Node *> remove_lowest(Node *root) {
    assert(root != nullptr);
    if (root->left == nullptr) {
      return {root, root->right};
    } else {
      auto [removed_node, new_root_left] = remove_lowest(root->left);
      root->left = new_root_left;
      return {removed_node, root};
    }
  }

  static void display(Node *root, std::ostream &out) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->elem;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
  set.display(out);
  return out;
}


using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado EOF
//Coste: O(n*m) donde n es el numero de jugadores y m es el numero de cartas
//de la baraja. Recorre m veces el bucle for para insertar y las llamadas a 
//los metodos insert, erase y constains O(n)
bool tratar_caso() {
  // Implementar.

    int n, m;
    cin >> n >> m;
    if (!cin)
        return false;
    
    vector<SetTree<int>> jugadores;
    for (int i = 0; i < n; i++) {
        SetTree<int> arbol;
        jugadores.push_back(arbol);
    }
    int x, pos;
    for (int j = 0; j < m; j++) {
        cin >> x;
        pos = j % n;
        if (!jugadores[pos].contains(x)) {
            jugadores[pos].insert(x);
        }
        else {
            jugadores[pos].erase(x);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << "J" << i+1 << ": ";
        jugadores[i].display(cout);
        cout << endl;
    }
    cout << "---" << endl;
    return true;
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>



int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  system("PAUSE");
#endif
  return 0;
}

