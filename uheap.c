#include <inc/lib.h>
#define heap_size (USER_HEAP_MAX - USER_HEAP_START)

uint32 frame_adresses[heap_size / PAGE_SIZE + 1];
uint32 frame_sizes[heap_size / PAGE_SIZE + 1];
uint32 frame_is_full[heap_size / PAGE_SIZE + 1];

void* malloc(uint32 size) {
	size = ROUNDUP(size, PAGE_SIZE);
	uint32	no_of_free_frames = 0;
	uint32 addr_of_best_fit = -1;
	uint32 Best_fit_size = (heap_size + 2*PAGE_SIZE);
	frame_is_full[((heap_size) / PAGE_SIZE)]= 1;
	for (uint32 i = 0; i <= ((heap_size) / PAGE_SIZE);	i++) {
		if (frame_is_full[i] == 0)  //consecuitve empty frames
			no_of_free_frames += PAGE_SIZE;
		 else {
			if (no_of_free_frames >= size) { //check if number of free frames can hold the sizes
				if (no_of_free_frames < Best_fit_size) {
					addr_of_best_fit = ((USER_HEAP_START + (i * PAGE_SIZE)) - no_of_free_frames);
					Best_fit_size = no_of_free_frames;
				}
			}
			no_of_free_frames = 0;
		}
	}
	if (addr_of_best_fit == -1)//no best fit address
		return NULL;
	else {
		sys_allocateMem(addr_of_best_fit, size);
		for (int i = 0; i < size / PAGE_SIZE; i++) {
			frame_is_full[(addr_of_best_fit - USER_HEAP_START) / PAGE_SIZE + i] = 1;
		}
		frame_sizes[((addr_of_best_fit- USER_HEAP_START) / PAGE_SIZE)] = size;
		frame_adresses[((addr_of_best_fit - USER_HEAP_START) / PAGE_SIZE)] = addr_of_best_fit;
	}
	return (void*)addr_of_best_fit;
}
/*
 uint32 virtual = 0;
	int findInAllocated = 1;


	    int x = ROUNDUP(size , PAGE_SIZE) ;
		int number_page = x/ PAGE_SIZE ;
		int difference=USER_HEAP_MAX-USER_HEAP_START;
		int index_of_diff=-1;
		for (int i=0;i<global;i++){
			if(still_allocate[i]==1){
			for (int j =0;j<global;j++){
				if (still_allocate[j]==1&&address[i]+sizes[i]==address[j])
				{
					sizes[i]=sizes[i]+sizes[j];
					sizes[j]=0;
					still_allocate[j]=0;
					//j=-1;

				}
			}

			}
		}
		for (int i = 0; i<global+1;i++) {
				if (still_allocate[i]!=0&&sizes[i]>=x&&difference>sizes[i]-x)
				{
					difference=sizes[i]-x;
					index_of_diff=i;
				}
			}
			if (index_of_diff != -1) {
				sizes[index_of_diff]=x;
				address[global]=address[index_of_diff]+x;
				sizes[global]=difference;
				still_allocate[global]=1;
				still_allocate[index_of_diff]=0;
			global++;
			sys_allocateMem(address[index_of_diff] , x) ;
			return (void*)address[index_of_diff];
			}

		if(current+x>=USER_HEAP_START&&current+x<USER_HEAP_MAX)
		{


				sys_allocateMem(current , size) ;
				global++;
				address[global] = current ;
				sizes[global] = x ;
				still_allocate[global] = 0 ;
				current+=x ;

				return (void * )(current -x) ;

		}
		return NULL;

  return NULL;

 */
// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address) {
	//TODO: [PROJECT 2021 - [2] User Heap] free() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("free() is not implemented yet...!!");
	//you should get the size of the given allocation using its address
	//refer to the project presentation and documentation for details
	for (int i = 0; i < ((heap_size) / PAGE_SIZE); i++) {
		if (frame_adresses[i] == (uint32) virtual_address) {
			sys_freeMem((uint32) virtual_address, frame_sizes[i]);
	int no_of_frames = frame_sizes[i] / PAGE_SIZE;
			for (int looper = 0; looper < no_of_frames; looper++) {
				frame_is_full[looper+i] = 0;
				frame_adresses[looper+i ]= 0;
				frame_sizes[looper+i]= 0;
			}
		}

	}
}


//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable) {
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName) {
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address) {
	panic("this function is not required...!!");
}

void *realloc(void *virtual_address, uint32 new_size) {
	panic("this function is not required...!!");
	return 0;
}

void expand(uint32 newSize) {
	panic("this function is not required...!!");
}
void shrink(uint32 newSize) {
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address) {
	panic("this function is not required...!!");
}
