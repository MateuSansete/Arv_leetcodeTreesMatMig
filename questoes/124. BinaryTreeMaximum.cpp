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
private:
    // max_sum | Variavel para rastrear a resposta final
    long max_sum; 

public:
    int maxPathSum(TreeNode* root) {
        // Inicializa com o menor valor inteiro possível
        max_sum = (long)INT_MIN; 
        
        dfs(root);
        
        return (int)max_sum;
    }

private:
    // Função auxiliar que retorna o "ganho máximo em linha reta"
    int dfs(TreeNode* node) {
        // 1. Caso base
        if (node == nullptr) {
            return 0;
        }

        // 2. Chama recursivamente para esquerda e direita.
        // Usa max(0,...) para ignorar caminhos com soma negativa.
        int left_gain = std::max(0, dfs(node->left));
        int right_gain = std::max(0, dfs(node->right));

        // 3. Calcula o "caminho dobrado" neste nó
        // E atualiza a resposta global se for o maior encontrado
        int path_with_split = node->val + left_gain + right_gain;
        max_sum = std::max(max_sum, (long)path_with_split);

        // 4. Retorna o "ganho reto" para o nó pai
        // (o nó atual + o melhor dos seus dois filhos)
        return node->val + std::max(left_gain, right_gain);
    }
};