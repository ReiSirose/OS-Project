#include <unistd.h>
#include <sys/mman.h>
#include <iostream>   // For debugging output
#include <cstddef>    // For size_t
#include <mutex>      // For thread-safety later

constexpr size_t INITIALIZE_HEAP_SIZE {4096};
constexpr int CHECK_SUM {123456};
size_t CURRENT_HEAP_SIZE {};

// FINSIHED: Resolve type mismatch
typedef struct {
    size_t size;
    bool free;
    Blockheader* next;
    Blockheader* prev;
}Blockheader;

// TODO: Need to be thread safe (make it more finer lock to improved multithreaded performance)
void* Heap {nullptr};
Blockheader* Head {nullptr};
std::mutex heap_mutex {};

// FINISHED: Initialize the heap
void HeapInit(size_t heap_size){
    std::lock_guard <std::mutex> lock (heap_mutex);
    // Hint: Use mmap() to allocate a block
    if(heap_size == 0){
        std::cerr << "Error, Heap can't be zero" << std::endl;
        return;
    }
    if(heap_size < sizeof(Blockheader)){
        std::cerr << "Error, Heap is too small" << std::endl;
        return;
    }

    Heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if(Heap == MAP_FAILED){
        perror("Map failed");
        Heap = nullptr;
        return;
    }

    Head = static_cast<Blockheader*> (Heap);
    Head->free = true;
    Head->size = heap_size - sizeof(Blockheader);
    Head->next = nullptr;
    Head->prev = nullptr;
    
    CURRENT_HEAP_SIZE = heap_size;
    std::cout << "Successfully initialized the heap with size of " << heap_size << " bytes" << std::endl;
    std::cout << "The head of the free list start at location " << static_cast<void*> (Head) << std::endl;
}



// FINISHED: Search through free block linkedlist and choose the first fit
// TODO: Implement previous pointer for future coalesing
void* Malloc(size_t size){
    // Hint: split the block and update the linkedlist after allocate the block

    std::lock_guard <std::mutex> lock (heap_mutex);
    Blockheader* current = Head;
    size_t user_allocated_block = static_cast<size_t>(sizeof(Blockheader)) + size;
    while(current != nullptr){
        if(current->free && current->size >= size){
            break;
        }
        current = current->next;
    }
    // TODO: provide option to extended the heap for space
    if(current == nullptr){
        std::cout << "No available free space left" << std::endl;
        void* newHeap = mremap(Heap, CURRENT_HEAP_SIZE, CURRENT_HEAP_SIZE * 2, MREMAP_MAYMOVE);
        if(newHeap == MAP_FAILED){
            std::cout << "Failed to expanded more space" << std::endl;
            return current;
        }
        else{
            std::cout << "Acquired more space" << std::endl;
            // old address become new address
            Heap = newHeap;
            // this is the start of the new additional block offset (old_addr + previous_size)
            current = (Blockheader*)((char*)Heap + CURRENT_HEAP_SIZE);
            // then update the heap size
            current->free = true;
            current->size = CURRENT_HEAP_SIZE - static_cast<size_t>(sizeof(Blockheader)); // the additional old current heap size - the blockheader size is free
            CURRENT_HEAP_SIZE *= CURRENT_HEAP_SIZE * 2; // update the current heap size
            // TODO: Think about the pointer later (to connect the last head)


            Head = current;
        }
    }

    // This the remaining size
    size_t remaining = current->size - user_allocated_block;
    if(remaining >= static_cast<size_t>(sizeof(Blockheader))){
         // update the new head
        Blockheader* newHead = (Blockheader*) ((char*)current + user_allocated_block);
        newHead->size = remaining;
        newHead->free = true;
        newHead->next = current->next;
        Head = newHead;
    }
    else{
        // make the old head as meta data for the allocated block
        current->free = false;
        current->size = size;
        current->next = nullptr;
    }
    void* user_pointer = (char*)(current) + sizeof(Blockheader);
    
    return user_pointer;
}

// FINISHED: Just mark it free in the blockheader and not worry about coalesing
// TODO: INPUT SANITIZING, pointer validation
// TODO: Try to coalesing block next to each other
void Free(void* ptr){
    // given the user pointer, index 1 sizeof(Blockerheader) back to get to the metadata
    std::lock_guard <std::mutex> lock (heap_mutex);
    if(ptr != nullptr){
        Blockheader* header = (Blockheader* )((char *)ptr - sizeof(Blockheader));
        // double free prevention
        if(header->free == false){
            header->free = true;
            Blockheader* old_head = Head;
            Head = header;
            header->next = old_head;
        }
    }
}

// FINISHED: Add deallocate mapped memory after finished
void HeapDestroy(size_t heap_size){
    if(Heap != nullptr){
        munmap(Heap, heap_size);
        Heap = nullptr;
        Head = nullptr;
    }
}

int main (int argc, char* argv){
    HeapInit(INITIALIZE_HEAP_SIZE);





    HeapDestroy(CURRENT_HEAP_SIZE);
}