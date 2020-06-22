#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    post_office* office;
    package* p;
    printf("%s:\n",t.name);
    for(int i = 0; i < t.offices_count; i++){
        office = t.offices + i;
        printf("\t%d:\n",i);
        for(int j = 0; j < office->packages_count; j++){
            p = office->packages + j;
            printf("\t\t%s\n",p->id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    
    int ok_packages = 0;
    post_office *so = source->offices + source_office_index;
    post_office *to = target->offices + target_office_index;
    package *p;
    for(int i = 0; i < so->packages_count; i++){
        p = so->packages + i;
        if( (p->weight >= to->min_weight) && (p->weight <= to->max_weight) )
            ok_packages++;
    }
    if(ok_packages == 0)
        return;
    package* new_sp = malloc( (so->packages_count - ok_packages) * sizeof(package) );
    package* new_tp = malloc( (to->packages_count + ok_packages) * sizeof(package) );
    memcpy(new_tp, to->packages, to->packages_count * sizeof(package));
    int index_newsp = 0, index_newtp = to->packages_count;
    for(int i = 0; i < so->packages_count; i++){
        p = so->packages + i;
        if( (p->weight >= to->min_weight) && (p->weight <= to->max_weight) ){
            *(new_tp + index_newtp++) = *(so->packages + i);
    }
        else{
            *(new_sp + index_newsp++) = *(so->packages + i);
        }
    }
    free(to->packages);
    free(so->packages);
    to->packages = new_tp;
    to->packages_count += ok_packages;
    so->packages = new_sp;
    so->packages_count -= ok_packages;
}

int count_packages_in_town(town* t){
    int np = 0;
    post_office* o;
    for(int i = 0; i < t->offices_count; i++){
        o = t->offices + i;
        np += o->packages_count;
    }
    return np;
}

town town_with_most_packages(town* towns, int towns_count) {
    town *best = towns, *t;
    int packages_best, packages_current;
    packages_best = count_packages_in_town(best);

    for(int i = 1; i < towns_count; i++){
        t = towns + i;
        packages_current = count_packages_in_town(t);
        if(packages_current > packages_best){
            best = t;
            packages_best = packages_current;
        }    
    }
    return *best;
}

town* find_town(town* towns, int towns_count, char* name) {
    town* current;
    for(int i = 0; i < towns_count; i++){
        current = towns + i;
        if(strcmp(name, current->name) == 0)
            return current;
    }
    return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
