/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */
/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){
    k1 = -1;
    k2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    if(isEmpty()){
        k1 = 0;
        k2 = 0;
    } else {
        k2++;
    }
    if(k2 < data.size()){
        data.at(k2) = newItem;
    } else {
        data.push_back(newItem);
    }
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL()//*************CHECK THE .h FILE FOR MORE INFO, MIGHT BE INCOMPLETE RIGHT NOW***********
{
    T ret_value = peekL();
    if(k2 == k1) {                                  //If there is only one element left in the array set the integers to -1 to represent an empty array
        k2 = -1;
        k1 = -1;
    } else if(k2 - k1 <= k1 + 1){                   //If we need to downsize, copy the array into a new and smaller one
        std::vector<T> temp;
        for(int i = k1 + 1; i <= k2; i++){
            temp.push_back(data.at(i));
        }
        data = std::vector<T>();
        for(int i = 0; i < temp.size(); i++){
            data.push_back(temp.at(i));
        }
        k2 = data.size() - 1;
        k1 = 0;
    } else {
        k1++;
    }
    return ret_value;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR()//*************CHECK THE .h FILE FOR MORE INFO, MIGHT BE INCOMPLETE RIGHT NOW***********
{
    T ret_value = peekR();
    if(k2 == k1) {               //If there is only one element left in the array set the integers to -1 to represent an empty array
        k2 = -1;
        k1 = -1;
    } else if(k2 - k1 <= k1){                   //If we need to downsize, copy the array into a new and smaller one
        std::vector<T> temp;
        for(int i = k1; i < k2; i++){
            temp.push_back(data.at(i));
        }
        data = std::vector<T>();
        for(int i = 0; i < temp.size(); i++){
            data.push_back(temp.at(i));
        }
        k2 = data.size() - 1;
        k1 = 0;
    } else {
        data.pop_back();
        k2--;
    }
    return ret_value;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data.at(k1);
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data.at(k2);
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    if(k1 == -1 && k2 == -1){
        return true;
    }
    return false;
}
