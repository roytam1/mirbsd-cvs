#include <pthread.h>
#include <gc.h>

struct intpair {
	int car;
	struct intpair *cdr;
};

struct intpair *cons(int car, struct intpair *cdr) {
	struct intpair *pair =
		(struct intpair*) GC_MALLOC(sizeof(struct intpair));
	pair->car = car;
	pair->cdr = cdr;
	return pair;
}

struct intpair *reverse_acc(const struct intpair *list, struct intpair *res) {
	return (list == NULL) ? res :
		reverse_acc(list->cdr, cons(list->car, res));
}

struct intpair *reverse(const struct intpair *list) {
	return reverse_acc(list, NULL);
}

int main(int argc, char **argv) {
	struct intpair *list = cons(1, cons(2, cons(3, cons(4, NULL))));
	list = reverse(list);
	list = reverse(list);
	list = reverse(list);
	list = reverse(list);
	return 0;
}
