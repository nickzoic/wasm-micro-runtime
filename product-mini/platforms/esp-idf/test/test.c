int printf(const char *s, ...);

int main(int argc, char **argv)
{
    for (int i=0; i<10; i++) {
        printf("Hello world! %d\n", i);
    }
}
