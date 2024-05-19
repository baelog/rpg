int generate_request_id(void)
{
    static int i = 1;
    return i++;
}