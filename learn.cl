__kernel
void learn()
{
	size_t gid0 = get_global_id(0);
    size_t gid1 = get_global_id(1);
    size_t gsz0 = get_global_size(0);
    size_t ofst0= get_global_offset(0);
    size_t ofst1= get_global_offset(1);
    size_t lid0 = get_local_id(0);
    size_t lid1 = get_local_id(1);
    float faa = gid0 * 10.0 + gid1 * 1.0 + lid0 * 0.1 + lid1 * 0.01;
    printf("%0.2f\n", faa); 
}