int generate_request_id(void)
{
    static int i = 0;
    return ++i;
}