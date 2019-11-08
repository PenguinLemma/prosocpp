#ifndef INCLUDED_EPI_SINGLY_LINKED_LIST_HPP
#define INCLUDED_EPI_SINGLY_LINKED_LIST_HPP

#include <optional>
#include <utility>
#include <memory>

namespace epi {

template<typename T>
struct SLListNode
{
    T data;
    std::shared_ptr<SLListNode<T>> next;
};

}  // namespace epi

#endif  // INCLUDED_EPI_SINGLY_LINKED_LIST_HPP