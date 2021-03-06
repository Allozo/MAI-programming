def is_alpha(letter):
    return letter.isnumeric()


def is_betta(letter):
    return letter.isalpha() or letter == '_'


def is_gamma(letter):
    return letter in ['a', 'b', 'c', 'd', 'e', 'f']


def is_delta(letter):
    return letter in ['or', 'and', 'xor']


class AutoParser:
    def __init__(self, name_file):
        self.name_file = name_file
        self.table_lexem = []

    def get_text(self):
        buffer = []
        with open(self.name_file) as file:
            for line in file:
                buffer.append(line)
        return buffer

    def parser(self):
        buffer = self.get_text()
        list_lexem = []

        for string in buffer:
            stack = ''
            for letter in string:

                if letter in [';', '(', ')']:
                    list_lexem.append(stack)
                    list_lexem.append(letter)
                    stack = ''
                elif letter == '=' and stack == ':':
                    stack = ''
                    list_lexem.append(':=')
                elif letter in [' ', '\n']:
                    list_lexem.append(stack)
                    stack = ''
                else:
                    stack += letter

            if stack != '':
                list_lexem.append(stack)

            while '' in list_lexem:
                list_lexem.remove('')

        return list_lexem

    def create_table_lexen(self):
        list_lexem = self.parser()
        print(list_lexem)
        for lexem in list_lexem:
            # отберем ключевые слова
            if lexem in ['and', 'xor', 'not', 'or']:
                self.table_lexem.append(['Ключевое слово', lexem])

            # отберем разделители
            elif lexem in ['(', ')', ';']:
                self.table_lexem.append(['Разделитель', lexem])

            # отберем знак присваивания
            elif lexem == ':=':
                self.table_lexem.append(['Знак присваивания', lexem])

            # отберем идентификаторы
            elif is_betta(lexem[0]):
                for symbol in lexem:
                    if not (is_alpha(symbol) or is_betta(symbol) or symbol == '_'):
                        print(f'Ошибка разбора!')
                        print(f'Идентификатор {lexem} не принадлежит языку')
                        break
                        # return
                else:
                    self.table_lexem.append(['Идентификатор', lexem])

            # отберем числа
            elif is_alpha(lexem[0]):
                for symbol in lexem:
                    if not (is_alpha(symbol) or symbol in ['A', 'B', 'B', 'D', 'E', 'F']):
                        print(f'Ошибка разбора!')
                        print(f'Число {lexem} не принадлежит языку')
                        break
                        # return
                else:
                    self.table_lexem.append(['Число', lexem])

            # что-то непонятное ввели
            else:
                print(f"Ошибочный ввод: {lexem}")

    def print_table(self):
        for index, line in enumerate(self.table_lexem):
            number = '| № {:>3}'.format(index)
            lexema = '| {:>20} | '.format(line[0])
            value = '{:>10} |'.format(line[1])
            print('----------------------------------------------')
            print(f'{number} {lexema} {value}')
        print('----------------------------------------------')


def main():
    auto = AutoParser('one_test.txt')
    auto.create_table_lexen()
    auto.print_table()


if __name__ == '__main__':
    main()
