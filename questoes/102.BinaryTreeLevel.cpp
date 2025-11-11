/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Função que retorna uma lista de listas de inteiros, 
    // onde cada lista interna contém os valores dos nós em um nível da árvore.
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        // O resultado será um vetor de vetores de inteiros.
        std::vector<std::vector<int>> result;

        // Se a raiz for nula, a árvore está vazia, retorna um vetor vazio.
        if (root == nullptr) {
            return result;
        }

        // Fila para realizar a travessia em largura (BFS).
        std::queue<TreeNode*> q;
        // Adiciona a raiz à fila.
        q.push(root);

        // Enquanto a fila não estiver vazia, continua a travessia.
        while (!q.empty()) {
            // Obtém o número de nós no nível atual.
            int levelSize = q.size();
            // Vetor para armazenar os valores dos nós no nível atual.
            std::vector<int> currentLevel;

            // Processa todos os nós no nível atual.
            for (int i = 0; i < levelSize; ++i) {
                // Pega o nó da frente da fila.
                TreeNode* node = q.front();
                q.pop();

                // Adiciona o valor do nó atual ao vetor do nível atual.
                currentLevel.push_back(node->val);

                // Se o filho esquerdo existir, adiciona-o à fila.
                if (node->left != nullptr) {
                    q.push(node->left);
                }

                // Se o filho direito existir, adiciona-o à fila.
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            
            // Adiciona o vetor do nível atual ao resultado final.
            result.push_back(currentLevel);
        }

        return result;
    }
};