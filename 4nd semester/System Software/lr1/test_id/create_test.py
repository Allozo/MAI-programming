import random
import string


def generate_random_string(length):
    letters = string.ascii_letters
    rand_string = ''.join(random.choice(letters) for i in range(length))
    return rand_string + '\n'


def create_file_with_number_test(number):
    with open(f'list_id_{number}.txt', 'w') as f:
        for _ in range(number):
            d = generate_random_string(70)
            f.write(d)


if __name__ == '__main__':
    number_id_in_test = [10, 50, 100, 500, 1000, 1500, 2000]
    for num in number_id_in_test:
        create_file_with_number_test(num)
