#ifndef BINARY_SEARCH_TREE_H_INCLUDED
#define BINARY_SEARCH_TREE_H_INCLUDED

#define queue std::queue
#define cout std::cout

template<typename contentType>
class AVLtree{
private:
    struct Node{
        contentType content;
        int depth;
        Node *leftChild, *rightChild;
        Node():
            depth(1),
            leftChild(nullptr),
            rightChild(nullptr)
            {}
        Node(contentType _content):
            content(_content),
            depth(1),
            leftChild(nullptr),
            rightChild(nullptr)
            {}
        void printContent(){
            cout << content << std :: endl;
        }
    } *root;
    int getDepth(Node *node){
        if (node == nullptr) return 0;
        return node->depth;
    }
    Node *RightRotation(Node *node){
        Node *lft = node->leftChild;
        Node *T2 = lft->rightChild;

        lft->rightChild = node;
        node->leftChild = T2;

        node->depth = 1 + std::max(getDepth(node->leftChild), getDepth(node->rightChild));
        lft->depth = 1 + std::max(getDepth(lft->leftChild), getDepth(lft->rightChild));

        return lft;
    }
    Node *LeftRotation(Node *node){
        Node *rght = node->rightChild;
        Node *T2 = rght->leftChild;

        rght->leftChild = node;
        node->rightChild = T2;

        node->depth = 1 + std::max(getDepth(node->leftChild), getDepth(node->rightChild));
        rght->depth = 1 + std::max(getDepth(rght->leftChild), getDepth(rght->rightChild));

        return rght;
    }
    int getDifference(Node *z){
        if (z == nullptr) return 0;
        return getDepth(z->leftChild) - getDepth(z->rightChild);
    }
    Node *insertNode(Node *node, contentType key){
        if (node == nullptr) return (new Node(key));
        if (key < node->content) node->leftChild = insertNode(node->leftChild, key);
        else if (node->content < key) node->rightChild = insertNode(node->rightChild, key);
            else return node;
        node->depth = 1 + std::max(getDepth(node->leftChild), getDepth(node->rightChild));

        int difference = getDifference(node);

        if (difference > 1){
            if (key < node->leftChild->content) return RightRotation(node);
            else{
                node->leftChild = LeftRotation(node->leftChild);
                return RightRotation(node);
            }
        }else{
            if (difference < -1){
                if (node->rightChild->content < key) return LeftRotation(node);
                else{
                    node->rightChild = RightRotation(node->rightChild);
                    return LeftRotation(node);
                }
            }
        }
        return node;
    }
    Node *deleteNode(Node *ptr, contentType key){
        if (ptr == nullptr) return ptr;
        if (key < ptr->content){
            ptr->leftChild = deleteNode(ptr->leftChild, key);
        }else if (ptr->content < key){
            ptr->rightChild = deleteNode(ptr->rightChild, key);
        }else{
            if (ptr->leftChild == nullptr || ptr->rightChild == nullptr){
                Node *tmp;
                if (ptr->leftChild == nullptr) tmp = ptr->rightChild;
                else tmp = ptr->leftChild;
                if (tmp == nullptr){
                    tmp = ptr;
                    ptr = nullptr;
                }else *ptr = *tmp;
                free(tmp);
            }else{
                Node *tmp = ptr->rightChild;
                while(tmp->leftChild != nullptr) tmp = tmp->leftChild;
                ptr->content = tmp->content;
                ptr->rightChild = deleteNode(ptr->rightChild, tmp->content);
            }
        }
        if (ptr == nullptr) return ptr;
        ptr->depth = 1 + std::max(getDepth(ptr->leftChild), getDepth(ptr->rightChild));
        int difference = getDifference(ptr);
        if (difference > 1){
            if (getDifference(ptr->leftChild) > 1) return RightRotation(ptr);
            else{
                ptr->leftChild = LeftRotation(ptr->leftChild);
                return RightRotation(ptr);
            }
        }else{
            if (difference < -1){
                if (getDifference(ptr->rightChild) < -1) return LeftRotation(ptr);
                else{
                    ptr->rightChild = RightRotation(ptr->rightChild);
                    return LeftRotation(ptr);
                }
            }
        }
        return ptr;
    }
public:
    AVLtree():
        root(nullptr)
        {}
    void printTree(){
        if (root == nullptr) return;
        queue < Node* > q;
        q.push(root);
        while(!q.empty()){
            Node *node = q.front();
            q.pop();
            node->printContent();
            if (node->leftChild != nullptr) q.push(node->leftChild);
            if (node->rightChild != nullptr) q.push(node->rightChild);
        }
    }
    void print_if(bool f(contentType)){
        if (root == nullptr) return;
        queue < Node* > q;
        q.push(root);
        while(!q.empty()){
            Node *node = q.front();
            q.pop();
            if (f(node->content))
                node->printContent();
            if (node->leftChild != nullptr) q.push(node->leftChild);
            if (node->rightChild != nullptr) q.push(node->rightChild);
        }
    }
    void add(contentType _content){
        root = insertNode(root, _content);
    }
    void delete_if(bool f(contentType)){
        if (root == nullptr) return;
        bool found = true;
        while(found){
            found = false;
            queue < Node* > q;
            if (root == nullptr) return;
            q.push(root);
            while(!q.empty()){
                Node * node = q.front();
                q.pop();
                if (f(node->content)){
                    found = true;
                    root = deleteNode(root, node->content);
                    break;
                }else{
                    if (node->leftChild != nullptr) q.push(node->leftChild);
                    if (node->rightChild != nullptr) q.push(node->rightChild);
                }
            }
        }
    }
};

#endif // BINARY_SEARCH_TREE_H_INCLUDED
