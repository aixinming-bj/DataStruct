#include <vector>
#include <iostream>
#define MAXLEVEL 10
template <class T>
class skipListNode
{
public:
    class Node
    {
    public:
        T data_;

        std::vector<Node *> forward_;
        Node(const T &data, int level) : data_(data)
        {
            forward_ = std::vector<Node *>(level, nullptr);
        }
    };

    skipListNode()
    {
        maxLevel_ = 1;
        head_ = new Node(T(), MAXLEVEL);
    }

    T *find(T key)
    {
        Node *cur = head_;
        for (int level = maxLevel_ - 1; level >= 0; level--)
        {
            while (cur->forward_[level] != nullptr && cur->forward_[level]->data_ < key)
            {
                cur = cur->forward_[level];
            }
        }

        if (cur->forward_[0] != nullptr && cur->forward_[0]->data_ == key)
        {
            return &(cur->forward_[0]->data_);
        }

        return nullptr;
    }

    void insert(T key)
    {
        int level = randomLevel();

        std::vector<Node *> update = std::vector<Node *>(MAXLEVEL, nullptr);
        Node *cur = head_;
        for (int i = maxLevel_ - 1; i >= 0; i--)
        {
            while (cur->forward_[i] != nullptr && cur->forward_[i]->data_ < key)
            {
                cur = cur->forward_[i];
            }
            update[i] = cur;
        }

        // 找到元素
        if (cur->forward_[0] != nullptr && cur->forward_[0]->data_ == key)
        {

            return;
        }

        Node *newNode = new Node(key, level);

        if (level > maxLevel_)
        {
            for (int i = maxLevel_; i < level; i++)
            {
                update[i] = head_;
            }
            maxLevel_ = level;
        }
        for (int i = level - 1; i >= 0; i--)
        {
            newNode->forward_[i] = update[i]->forward_[i];
            update[i]->forward_[i] = newNode;
        }

        
    }

    void deleteKey(T key)
    {
        std::vector<Node *> updata = std::vector<Node *>(MAXLEVEL, nullptr);
        Node *cur = head_;
        for (int i = maxLevel_ - 1; i >= 0; i--)
        {
            while (cur->forward_[i] != nullptr && cur->forward_[i]->data_ < key)
            {
                cur = cur->forward_[i];
            }
            updata[i] = cur;
        }
        if (cur->forward_[0] != nullptr && cur->forward_[0]->data_ == key)
        {
            Node *del = cur->forward_[0];
            for (size_t j = 0; j < del->forward_.size(); j++)
            {
                updata[j]->forward_[j] = del->forward_[j];
            }
            delete del;
        }
        while (maxLevel_ > 1 && head_->forward_[maxLevel_ - 1] == nullptr)
        {
            maxLevel_--;
        }
    }

    void print()
    {
        std::cout << "skipListNode--------------------------start\n";
        std::cout << "level = " << maxLevel_ << std::endl;
        for (int i = maxLevel_ - 1; i >= 0; i--)
        {
            Node *cur = head_;
            while (cur->forward_[i] != nullptr)
            {
                std::cout << cur->forward_[i]->data_ << " ";
                cur = cur->forward_[i];
            }
            std::cout << std::endl;
        }
        std::cout << "skipListNode--------------------------end\n";
    }

private:
    int randomLevel()
    {
       
        int level = 1;
        while (rand() % 2 == 1)
        {
            level++;
        }
        
        level = (level > MAXLEVEL) ? MAXLEVEL : level;
        
        return level;
    }

private:
    Node *head_;
    int maxLevel_;
    
};

int main(void)
{

    skipListNode<int> list;
    list.insert(1);
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.insert(9);
    list.insert(11);
    list.insert(13);
    list.insert(15);
    
    list.print();
    list.deleteKey(3);
    list.print();
    return 0;
}