/*
 * This is the file in which you will implement the functionality required by
 * the assignment.  Make sure to add your name and @oregonstate.edu email
 * address below:
 *
 * Name: Chase Dunn
 * Email: dunnchas@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "products.h"
#include "dynarray.h"

 /*
  * This function should allocate and initialize a single product struct with
  * name, inventory, and price data.
  *
  * Params:
  *   name - a string containing the product's name.  Note that you'll have to
  *     make a copy of this string to store in the product struct instead of
  *     storing this string directly.
  *   inventory - an integer for how many of this product in the store
  *   price - the product's price
  *
  * Return:
  *   Should return a newly-allocated product structure whose fields are
  *   initialized with the values provided.
  */
struct product* create_product(char* name, int inventory, float price) {
	struct product *p = malloc(sizeof(*p));
	if (!p) return NULL;

	p->name = strdup(name);
	if (!p->name) {
		free(p);
		return NULL;
	}
	p->inventory = inventory;
	p->price = price;
	return p;
}

/*
 * This function should free all memory allocated by create_product() for a
 * single product.  This function must free all relevant memory and cannot
 * result in a memory leak.
 *
 * Params:
 *   product - a pointer to the product whose memory should be freed.  This
 *     function must free any memory allocated to the fields of this struct
 *     as well as memory allocated for the struct itself.
 */
void free_product(struct product* product) {
	if (!product) return;
	free(product->name);
	free(product);
}

/*
 * This function should create a struct product for each product represented
 * in the information provided in the function arguments, and it should store
 * those products in a dynamic array (i.e. struct dynarray) allocated by this
 * function.  In particular, you should create a dynamic array and insert new
 * product structs into it, such that the i'th product in the array has the
 * i'th name, the i'th inventory, and the i'th price from the provided arrays
 * arguments.  You should use your create_product() function to allocate and
 * initialize each product struct stored in the array, and you should use the
 * provided dynamic array functions to allocate and work with the dynamic
 * array.  At the end of the function, you should return the dynamic array
 * with product structures stored in it.
 *
 * Params:
 *   num_products - the number of products to be stored in the newly allocated
 *     dynamic array
 *   names - an array of the names of the products to be stored in the dynamic
 *     array of product structs.  This array will have length num_products.
 *   inventory - an array of the inventory values, how many of the products in
 *   the store.
 *     array of product structs.  This array will have length num_products.
 *   prices - an array of the product prices to be stored in the dynamic
 *     array of product structs.  This array will have length num_products.
 *
 * Return:
 *   Should return a pointer to the newly allocated dynamic array containing
 *   newly-created product structs.  The i'th product in this array should have
 *   the i'th name, the i'th inventory, and the i'th price from the arrays provided as
 *   arguments.
 */
struct dynarray* create_product_array(int num_products,
	char** names,
	int* inventories,
	float* prices) {
	struct dynarray *arr = dynarray_create();
	if (!arr) return NULL;

	for (int i = 0; i < num_products; i++) {
		struct product *p = create_product(names[i], inventories[i], prices[i]);
		if (!p) {
			free_product_array(arr);
			return NULL;
		}
		dynarray_insert(arr, -1, p);
	}
	return arr;
}


/*
 * This function should free all of the memory allocated to a dynamic array of
 * product structs, including the memory allocated to the array itself as
 * well as any memory allocated to the individual product structs.  You
 * should use free_product() to free the memory for each individual product,
 * and you should use provided dynamic array functions to free the memory
 * associated with the dynamic array itself.  This function must free *all*
 * memory associated with a dynamic array of products and must not result in
 * any memory leaks.
 *
 * Params:
 *   products - a pointer to the dynamic array of product structs whose memory
 *     is to be freed
 */
void free_product_array(struct dynarray* products) {
	if (!products) return;
	int n = dynarray_length(products);
	for (int i = 0; i < n; i++) {
		struct product *p = dynarray_get(products, i);
		free_product(p);
	}
	dynarray_free(products);
}

/*
 * This function should print the name, inventory, and price of products in an
 * array, one product per line.  You must use provided dynamic array functions
 * to access the product data stored in the array.
 *
 * Params:
 *   products - the dynamic array of products to be printed
 */
void print_products(struct dynarray* products) {
	int n = dynarray_length(products);
	for (int i = 0; i < n; i++) {
		struct product *p = dynarray_get(products, i);
		printf("Name: %s, Inventory: %d, Price: $%.2f\n",
			p->name, p->inventory, p->price);
	}
}

/*
 * This function should return a pointer to the product in a given array with
 * the highest price.  You should not make a copy of the product being returned,
 * i.e. this function should not allocate any memory.  Instead, you should
 * simply return the pointer to the product struct that's already stored in
 * the array.  You must use the provided dynamic array functions to access
 * the data stored in the array.
 *
 * Params:
 *   products - the array from which to find the product with the highest price
 *
 * Return:
 *   Should return a pointer to the product in the array with the highest price.
 *   You should not make a copy of the product being returned but should
 *   instead return the pointer to the product struct that's already stored in
 *   the array.
 */
struct product* find_max_price(struct dynarray* products) {
	int n = dynarray_length(products);
	if (n == 0) return NULL;

	struct product *max_p = dynarray_get(products, 0);
	for (int i = 1; i < n; i++) {
		struct product *p = dynarray_get(products, i);
		if (p->price > max_p->price) {
			max_p = p;
		}
	}
	return max_p;
}

/*
 * This function should return a pointer to the product in a given array with
 * the largest investment, defined as the product of inventory and price.
 * investment = inventory*price, meaning how many does the store have times
 * how many
 * You should not make a copy of the product being returned,
 * i.e. this function should not allocate any memory.  Instead, you should
 * simply return the pointer to the product struct that's already stored in
 * the array.  You must use the provided dynamic array functions to access
 * the data stored in the array.
 *
 * Params:
 *   products - the array from which to find the product with the lowest price
 *
 * Return:
 *   Should return a pointer to the product in the array with the highest
 *   investment = price*investment.
 *   You should not make a copy of the product being returned but should
 *   instead return the pointer to the product struct that's already stored in
 *   the array.
 */
struct product* find_max_investment(struct dynarray* products) {
	int n = dynarray_length(products);
	if (n == 0) return NULL;

	struct product *best = dynarray_get(products, 0);
	float best_inv = best->inventory * best->price;

	for (int i = 1; i < n; i++) {
		struct product *p = dynarray_get(products, i);
		float inv = p->inventory * p->price;
		if (inv > best_inv) {
			best_inv = inv;
			best = p;
		}
	}
	return best;
}


/*
 * This function should sort the products stored in a dynamic array by
 * ascending inventory (i.e. lowest inventory at the beginning of the array).
 * You may implement any sorting algorithm you want, with the following
 * constraints:
 *   - You must sort in place, i.e. you can't allocate additional memory.
 *   - You may not use built-in sorting functions like qsort(), i.e. you must
 *     implement the sort yourself.  You may implement any in-place sorting
 *     algorithm you like.  Some possibilities are selection sort, insertion
 *     sort, bubble sort, and quicksort.
 *   - You must use provided dynamic array functions (e.g. dynarray_get(),
 *     dynarray_set(), etc.) to access and modify the contents of the dynamic
 *     array.
 *
 * Params:
 *   products - the dynamic array of products to be sorted.  When the function
 *   returns, this array should be sorted by ascending inventory (lowest to
 *   highest).
 */
void sort_by_inventory(struct dynarray* products) {
	int n = dynarray_length(products);
	if (n < 2) return;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			struct product *p1 = dynarray_get(products, j);
			struct product *p2 = dynarray_get(products, j + 1);
			if (p1->inventory > p2->inventory) {
				dynarray_set(products, j, p2);
				dynarray_set(products, j + 1, p1);
			}
		}
	}
}