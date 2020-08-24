#include <vector>
#include <algorithm>
#include <iostream>
template <class T>
class priority_queue
{
public:
    //留0位置
    priority_queue()
    {
        Vec_.push_back(T());
    }

    T front()
    {
        return Vec_[1];
    }

    void pop()
    {
        std::swap(Vec_[1], Vec_[Vec_.size() - 1]);
        Vec_.pop_back();
        adjust_priority_queue(1);
    }

    void push(T Value)
    {
        Vec_.push_back(Value);
        size_t index = Vec_.size() - 1;
        while (index > 1)
        {
            size_t parent = index / 2;
            if (Vec_[parent] >= Value)
            {
                break;
            }
            else
            {
                Vec_[index] = Vec_[parent];
                index = parent;
            }
        }
        Vec_[index] = Value;
    }

    bool empty()
    {
        return Vec_.size() == 1;
    }

    void print()
    {
        for (auto &value : Vec_)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

private:
    void adjust_priority_queue(int index)
    {
        size_t len = Vec_.size() - 1;
        T data = Vec_[index];
        //size_t larger = index;
        while (index <= len / 2)
        {

            size_t left = index * 2;
            size_t right = index * 2 + 1;
            if (right <= len)
            {
                if (data > Vec_[left] && data > Vec_[right])
                {
                    break;
                }
                if (Vec_[left] > data && Vec_[left] > Vec_[right])
                {
                    Vec_[index] = Vec_[left];
                    index = left;
                    //larg
                    continue;
                }
                if (Vec_[right] > data && Vec_[right] > Vec_[left])
                {
                    Vec_[index] = Vec_[right];
                    index = right;
                    continue;
                }
            }
            else
            {
                if (data > Vec_[left])
                {
                    break;
                }
                Vec_[index] = Vec_[left];
                index = left;
            }
        }

        Vec_[index] = data;
    }
    void build_priority_queue()
    {
        size_t length = Vec_.size() - 1;
        for (size_t i = length / 2; i > 0; i--)
        {
            adjust_priority_queue(i);
        }
    }

private:
    std::vector<T> Vec_;
};

int main(void)
{
    priority_queue<int> heap;
    heap.push(4);
    heap.push(1);
    heap.push(3);
    heap.push(2);
    heap.push(16);
    heap.push(9);
    heap.push(10);
    heap.push(14);
    heap.push(8);
    heap.push(7);
    //heap.print();
    while (!heap.empty())
    {
        std::cout << heap.front() << " ";
        heap.pop();
        
    }
    std::cout << std::endl;
    return 0;
}