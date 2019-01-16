#include <vector>
#include <exception>
#include <stdexcept>
#include <math.h>

template <class T>
class MinHeap {
public:
       /* Constructor that builds a d-ary Min Heap
          his should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
       MinHeap (int d_count)
       {
            if(d_count >= 2)
            {
                d = d_count;
            }
       }
       
       ~MinHeap ()
       {
          
       }

       void add (T item, int priority)
       {
            /* adds the item to the heap, with the given priority. */

            std::pair<T,int> element(item, priority);
            heap.push_back(element);

            //if it's the first one then just push_back and do nothing more
            if(heap.size() == 1)
                return;

            //bubble up to where it belongs, assume that the heap up to now is maintained

            //starts at end of heap, root node will be in place at this point
            int currentLocation = heap.size()-1;
            int parentLocation = (currentLocation-1) / d;

            //while it is smaller than its its parent's priority and not at the top, swap
            while(priority < heap[parentLocation].second && currentLocation != 0)
            {
                //swap
                std::pair<T,int> temp(heap[parentLocation].first, heap[parentLocation].second);
                heap[parentLocation] = heap[currentLocation];
                heap[currentLocation] = temp;

                //update current and parent locations
                currentLocation = parentLocation;
                parentLocation = (currentLocation-1) / d;
            }
       }

       const T & peek () const
       {
            /* returns the element with smallest priority.  
               Break ties however you wish.  
               Throws an exception if the heap is empty. */
            
            if(heap.size() == 0)
            {
                throw std::logic_error("heap is empty");
            }

            return heap[0].first;
       }

       void remove ()
       {
          /* removes the element with smallest priority.
            Break ties however you wish.
            Throws an exception if the heap is empty. */

          if(heap.size() == 0)
          {
              throw std::logic_error("heap is empty");
          }

          if(heap.size() == 1)
          {
              heap.erase(heap.begin());
              return;
          }

          //otherwise swap with bottom, pop bottom then trickle down the top

          //swap top and bottom of heap
          std::pair<T,int> temp(heap[0].first, heap[0].second);
          heap[0] = heap[heap.size()-1];
          heap[heap.size()-1] = temp;

          //pop bottom (aka now the smallest priority) so the end of heap
          heap.erase(heap.begin() + heap.size()-1);

          //trickle down the top element to where it belongs
          int currentLocation = 0;
          bool isLargerThanChildren = true;
          //this segment will loop if the element is larger than any of its children
          //or at end of heap, then swap w smallest child
          do {
              //if the node has no more children left, aka where its first child should be is OOB
              //effectively at bottom of heap, so it is in place
              if(currentLocation*d+1 >= (int)heap.size())
              {   
                  //finished, no children so at effective "bottom level" of heap, in place
                  break;
              }

              //childrens' location will be at currentLocation*d+1 up to currentLocation*d+d
              int smallestLocation = currentLocation*d+1;
              int smallestChildPriority = heap[smallestLocation].second;
              for(int i = 0; i < d; i++)
              { 
                  //check child's bounds to make sure it exists
                  if(currentLocation*d+1+i < (int)heap.size())
                  {
                      //iterate thru children, find smallest priority to switch with
                      if(heap[currentLocation*d+1+i].second < smallestChildPriority)
                      {
                          smallestChildPriority = heap[currentLocation*d+1+i].second;
                          smallestLocation = currentLocation*d+1+i;
                      }
                  }
              }


              //check greater than condition here is still valid to swap, aka is larger than at least 1 child 
              //smallestChild will be in bounds here as we checked that the element has at least 1 child first
              if(heap[currentLocation].second <= smallestChildPriority)
              {   
                  //finish here, it is in place where it is smaller than or equal to all of its children
                  break;
              }

              //it is legal to swap here, all conditions have been met: 
              //has children to swap with, is larger than at least one of its children, so swap with smallest child
              std::pair<T,int> tempstorage(heap[currentLocation].first, heap[currentLocation].second);
              heap[currentLocation] = heap[smallestLocation];
              heap[smallestLocation] = tempstorage;

              //update currentLocation to where it swapped to, follow the node we are trickling down
              currentLocation = smallestLocation;


              //check children again for the next iteration, for updated currentLocation
              //if empty, it will catch this and break on the next iteration.
              isLargerThanChildren = false;
              for(int i = 0; i < d; i++)
              {
                  //placeholder for the child of our updated element we are iterating through
                  int thisChildLocation = currentLocation*d+1 + i;
                  //check bounds first of each child's location
                  if(thisChildLocation < (int)heap.size())
                  {   //if our node is larger than any of its children
                      if(heap[currentLocation].second > heap[thisChildLocation].second)
                      {
                          isLargerThanChildren = true;
                      }
                  }
              }

          } while(isLargerThanChildren);

       }

       bool isEmpty ()
       {
            /* returns true iff there are no elements on the heap. */
            return (heap.size() == 0);
       }

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.

      //store item and priority as pairs within the vector
      std::vector< std::pair<T,int> > heap;
      int d;
  };