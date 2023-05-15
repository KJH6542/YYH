#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 상품 구조체 선언 (상품명, 가격)
typedef struct {
	char name[30];
    int price;
} Product;
Product product, products[50], existing_product;
FILE *fp; // File Product -> fp

// 고객 구조체 선언 (이름, 주소, 전화번호)
typedef struct {
    char name[30];
    char address[100];
    char phone[20];
} Customer;
Customer customer, customers[50], existing_customer;
FILE *fc; // File Customer -> fc

// 주문 구조체 선언 (주문 ID, 상품명, 고객이름, 수량, 주문 날짜)
typedef struct {
    char order_id[20];
    char product_name[30];
    char customer_name[30];
    int quantity;
    char order_date[20];
} Order;
Order order, orders[50], existing_order;
FILE *fo; // File Order -> fo

int main() {
    int choice;
    while (1) {
    	printf("\n");
        printf("1. 상품 관리\n");
        printf("2. 고객 관리\n");
        printf("3. 주문 관리\n");
        printf("4. 종료\n");
        printf("번호를 고르시오: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                product_m();
                break;
            case 2:
                customer_m();
                break;
            case 3:
                order_m();
                break;
            case 4:
                exit(0);
            default:
                printf("잘못된 숫자를 입력하셨습니다.\n");
        }
    }
    return 0;
}

void product_m() {
	int choice_p;
    while (1) {
    	printf("\n");
        printf("1. 상품 추가\n");
        printf("2. 상품 수정\n");
        printf("3. 상품 삭제\n");
        printf("4. 상품 목록\n");
        printf("5. 뒤로가기\n");
        printf("번호를 고르시오: ");
        scanf("%d", &choice_p);
        switch (choice_p) {
            case 1:
                product_add();
                break;
            case 2:
                product_mod();
                break;
            case 3:
                product_del();
                break;
            case 4:
                product_list();
                break;
            case 5:
            	main();
                break;
            default:
                printf("잘못된 숫자를 입력하셨습니다.\n");
        }
    }
}

void customer_m() {
	int choice_c;
    while (1) {
    	printf("\n");
        printf("1. 고객 추가\n");
        printf("2. 고객 수정\n");
        printf("3. 고객 삭제\n");
        printf("4. 고객 목록\n");
        printf("5. 뒤로가기\n");
        printf("번호를 고르시오: ");
        scanf("%d", &choice_c);
        switch (choice_c) {
            case 1:
                customer_add();
                break;
            case 2:
                customer_mod();
                break;
            case 3:
                customer_del();
                break;
            case 4:
                customer_list();
                break;
            case 5:
                main();
                break;
            default:
                printf("잘못된 숫자를 입력하셨습니다.\n");
        }
    }
}

void order_m() {
	int choice_o;
    while (1) {
    	printf("\n");
        printf("1. 주문 추가\n");
        printf("2. 주문 수정\n");
        printf("3. 주문 삭제\n");
        printf("4. 주문 목록\n");
        printf("5. 뒤로가기\n");
        printf("번호를 고르시오: ");
        scanf("%d", &choice_o);
        switch (choice_o) {
            case 1:
                order_add();
                break;
            case 2:
                order_mod();
                break;
            case 3:
                order_del();
                break;
            case 4:
                order_list();
                break;
            case 5:
                main();
                break;
            default:
                printf("잘못된 숫자를 입력하셨습니다.\n");
        }
    }
}

void product_add() {
	int pa_count = 0, pa_duplicate = 0;

    fp = fopen("상품.txt", "a+"); // 상품 정보 파일 열기 (추가 모드)

    if (fp == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
	printf("\n");
	printf("상품명을 입력하시오.: ");
    scanf("%s", product.name);
    printf("상품의 가격을 입력하시오.: ");
    scanf("%d", &product.price);
    
    while (fscanf(fp, "%s %d", existing_product.name, &existing_product.price) != EOF) {
        if (strcmp(existing_product.name, product.name) == 0) {
            pa_duplicate = 1;
            break;
        }
    }
    
    if (pa_duplicate) {
        printf("상품이 이미 존재합니다.\n");
    } else {
        fprintf(fp, "%s %d\n", product.name, product.price); // 상품 정보 파일에 추가
        printf("\n");
    	printf("정상적으로 처리되었습니다.\n");
    }
    
    fclose(fp);
}

void product_mod() {
    char pm_file[] = "상품.txt";
    char pm_name[30];
    int pm_new_price;
    int pm_num_products = 0;
    int pm_i, pm_found = 0;
    
    fp = fopen("상품.txt", "r");
    
    if (fp == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
    while (fscanf(fp, "%s %d", products[pm_num_products].name, &products[pm_num_products].price) != EOF) {
        pm_num_products++;
    }
    fclose(fp);
    
    printf("수정할 상품명을 입력하세요: ");
    scanf("%s", pm_name);
    
    for (pm_i = 0; pm_i < pm_num_products; pm_i++) {
        if (strcmp(pm_name, products[pm_i].name) == 0) {
            pm_found = 1;
            break;
        }
    }
    
    if (pm_found) {
        printf("새로운 가격을 입력하세요: ");
        scanf("%d", &pm_new_price);
        
        products[pm_i].price = pm_new_price;
        
        // 파일에 수정된 상품 정보 저장
        fp = fopen("상품.txt", "w");
        
        if (fp == NULL) { // 파일이 없을 경우 예외 처리
            printf("Error: 파일을 찾을 수 없습니다.\n");
            return 1;
        }
        
        for (pm_i = 0; pm_i < pm_num_products; pm_i++) {
            fprintf(fp, "%s %d\n", products[pm_i].name, products[pm_i].price);
        }
        
        fclose(fp);
        
        printf("%s 상품의 가격이 수정되었습니다.\n", pm_name);
    } else {
        printf("%s 상품을 찾을 수 없습니다.\n", pm_name);
    }
}

void product_del() {
	char pd_file[] = "상품.txt";
    char pd_name[30];
    int pd_num_products = 0;
    int pd_i, pd_found = 0;
    
    fp = fopen("상품.txt", "r");
    
    if (fp == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
    while (fscanf(fp, "%s %d", products[pd_num_products].name, &products[pd_num_products].price) != EOF) {
        pd_num_products++;
    }
    fclose(fp);
    
    // 상품 삭제하기
    printf("제거할 상품명을 입력하세요.: ");
    scanf("%s", pd_name);
    
    for (pd_i = 0; pd_i < pd_num_products; pd_i++) {
        if (strcmp(pd_name, products[pd_i].name) == 0) {
            pd_found = 1;
            break;
        }
    }
    
    if (pd_found) {
        // 해당 상품을 파일에서 제거
        fp = fopen("상품.txt", "w");
        for (pd_i = 0; pd_i < pd_num_products; pd_i++) {
            if (strcmp(pd_name, products[pd_i].name) != 0) {
                fprintf(fp, "%s %d\n", products[pd_i].name, products[pd_i].price);
            }
        }
        fclose(fp);
        
        printf("%s 상품을 제거했습니다.\n", pd_name);
    } else {
        printf("%s 상품을 찾을 수 없습니다.\n", pd_name);
    }
}

void product_list() {
	int pl_count = 0;
	fp = fopen("상품.txt", "r"); // 상품 정보 파일 열기
	
    if (fp == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
    printf("\n");
    printf("상품명\t\t가격\n");
    printf("------------\t-------------\n");
    
    while (fscanf(fp, "%s %d", product.name, &product.price) != EOF) {
        printf("%-15s\t$%d\n", product.name, product.price);
        pl_count++;
    }
    
    if (pl_count == 0) { // 파일이 비어있는 경우 예외 처리
        printf("추가된 상품이 없습니다.\n");
    }
    
    fclose(fp); // 파일 닫기
}

void customer_add() {
    char ca_file[] = "고객.txt";
    
    // 고객 정보 입력 받기
    printf("\n");
    printf("고객의 이름을 입력하세요: ");
    fgets(customer.name, 30, stdin);
    customer.name[strcspn(customer.name, "\n")] = '\0';  // 개행 문자 제거
    
    printf("고객의 주소를 입력하세요: ");
    fgets(customer.address, 100, stdin);
    customer.address[strcspn(customer.address, "\n")] = '\0';  // 개행 문자 제거
    
    printf("고객의 전화번호를 입력하세요: ");
    fgets(customer.phone, 20, stdin);
    customer.phone[strcspn(customer.phone, "\n")] = '\0';  // 개행 문자 제거
    
    fc = fopen("고객.txt", "r"); // 상품 정보 파일 열기 (추가 모드)

    if (fc == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
    char existing_name[30];
    while (fgets(existing_name, 30, fc) != NULL) {
        existing_name[strcspn(existing_name, "\n")] = '\0';  // 개행 문자 제거
        
        // 고객명이 이미 존재하는 경우 중복 확인
        if (strcmp(existing_name, customer.name) == 0) {
            char existing_address[100];
            char existing_phone[20];
            
            fgets(existing_address, 100, fc);
            fgets(existing_phone, 20, fc);
            existing_address[strcspn(existing_address, "\n")] = '\0';  // 개행 문자 제거
            existing_phone[strcspn(existing_phone, "\n")] = '\0';  // 개행 문자 제거
            
            fclose(fc);
            printf("고객명 '%s'은(는) 이미 존재합니다.\n", customer.name);
            printf("주소: %s\n전화번호: %s\n", existing_address, existing_phone);
            return 0;
        }
    }
    fclose(fc);
    
    fc = fopen("고객.txt", "a");
    
    if (fc == NULL) { // 파일이 없을 경우 예외 처리
        printf("Error: 파일을 찾을 수 없습니다.\n");
        return 1;
    }
    
    fprintf(fc, "%s\n%s\n%s\n", customer.name, customer.address, customer.phone);
    
    fclose(fc);
    printf("고객 정보가 파일에 추가되었습니다.\n");
}

void customer_mod() {
}

void customer_del() {
}

void customer_list() {
}

void order_add() {
}

void order_mod() {
}

void order_del() {
}

void order_list() {
}
