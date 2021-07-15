struct storage{
	int key;
};

struct information{
	char mask_left_edge;
	char mask_right_edge;
	struct storage *left_key;
	struct storage *right_key;
};




struct add_range_information32{
	unsigned int mask_left_edge;
	unsigned int mask_right_edge;
	char mask;
	struct storage* key_range;	
};

struct search32{
	unsigned int number;
	char mask_left_edge;
	char mask_right_edge;
	struct storage *left_key;
	struct storage *right_key;
};

struct top32{
	unsigned int number;
	char mask;
	struct top32 *left;
	struct top32 *right;
	struct storage *key_top;
	struct storage *key_range;
	char height;
};

