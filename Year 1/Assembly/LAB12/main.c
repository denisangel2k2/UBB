#include <stdio.h>

int substring(char sir1[], char sir2[]);

int main() {
	char sir1[101];
	char sir2[101];
	int n;

	scanf("%d", &n);
	scanf("%s", sir1);

	for (int i = 1; i <= n; i++) {
		scanf("%s", sir2);
			if (substring(sir1, sir2)) {
				printf("Subsir!\n");
		}
			else {
				printf("Nu e subsir!\n");
			}
	}
	return 0;
}