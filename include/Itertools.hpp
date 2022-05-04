/**
 * @file Itertools.hpp
 * @author Łukasz Kaniak - nativeme (lukaszkaniak@gmail.com)
 * @brief 
 * Simple wrappers on std algos (mostly std::find) just to simplify common
 * searching, selecting elements, chcecks ect. without need to specify
 * iterators outside.
 */

#ifndef _ITERTOOLS_HPP_
#define _ITERTOOLS_HPP_

#include "Arduino.h"

namespace softcast{
/**
 * @brief 
 * serches for an index of given element in given collection.
 * @tparam Indexed any iterable, indexed collecion.
 * @tparam T item wanted
 * @param collection source collecion
 * @param element item wanted
 * @return const int32_t index of item if found an item. -1 if item isn't found.
 */
template<typename Indexed, typename T>
const inline int32_t index_of(const Indexed &collection, const T &element){
    auto found = std::find(collection.begin(), collection.end(), element);
    if(found != collection.end())
      return std::distance(collection.begin(), found);
    return -1;
}

/**
 * @brief 
 * tries to find all elements of collection 2 inside collecion 1.
 * @tparam Iterable1 any iterable collection
 * @tparam Iterable2 any iterable collection
 * @param collection1 base collection
 * @param collection2 matched collection
 * @return bool true if all elements were found, false if less than all.
 */
template <typename Iterable1, typename Iterable2>
bool match_elements(const Iterable1& collection1, const Iterable2& collection2){
  uint16_t elem_count_target = collection2.size();
  uint16_t found_count = 0;

  for (auto &&col2_elem : collection2){
    auto found = std::find(collection1.begin(), collection1.end(), col2_elem);
    if (found != collection1.end())
      if(++found_count == elem_count_target)
        return true;
  }

  return false;
}

/**
 * @brief 
 * chcecks if collection contain all given elements.
 * @tparam Iterable any iterable collection
 * @tparam T first element fo find
 * @tparam Rest n number of elements to find 
 * @param collection base collection
 * @param wanted first element fo find
 * @param optional n number of elements to find
 * @return bool true if all elements were found, false if less than all.
 */
template<typename Iterable, typename T, typename... Rest>
const inline bool contains(const Iterable &collection, const T& wanted, const Rest& ...optional){
    if constexpr (sizeof...(Rest) > 0){
      auto wanted_list = {wanted, optional...};
      uint8_t found_size = 0;
      for (auto &&elem : wanted_list){
        auto found = std::find(collection.begin(), collection.end(), elem);
        if(found != collection.end())
          if(++found_size == wanted_list.size()) return true;
      }
    } else {
      auto found = std::find(collection.begin(), collection.end(), wanted);
      if(found != collection.end()) return true;
    }
    return false;
}

/**
 * @brief 
 * chcecks if collection contain at least one of given elements.
 * @tparam Iterable any iterable collection
 * @tparam T first element fo find
 * @tparam Rest n number of elements to find 
 * @param collection base collection
 * @param wanted first element fo find
 * @param optional n number of elements to find
 * @return bool true if on of elements was found, false none.
 */
template<typename Iterable, typename T, typename... Rest>
const inline bool contains_oneof(const Iterable &collection, const T& wanted, const Rest& ...optional){
    if constexpr (sizeof...(Rest) > 0){
      auto wanted_list = {wanted, optional...};
      for (auto &&elem : wanted_list){
        auto found = std::find(collection.begin(), collection.end(), elem);
        if(found != collection.end()) return true;
      }
    } else {
      auto found = std::find(collection.begin(), collection.end(), wanted);
      if(found != collection.end()) return true;
    }
    return false;
}
}
#endif