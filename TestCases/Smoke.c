int main() {
    int a[1];
    if (1 == 2) {
        int i;
        write(1 / 0);
        a[998244353] = 100;
        write(a[998244353]);
        i = 0;
        while (1) {
            a[i] = i + 1 + a[i - 1];
            i = i + 1;
            write(a[i]);
        }
        a[-999999] = 87;
        write(a[-999999]);
    } else {
        write(0);
    }
    return 0;
}
