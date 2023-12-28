1. _atoi.c code


#include "shell.h"

/**
 * interactive - this will return true if the shell is in interactive mode
 * @info: this is the struct address
 *
 * Return: should return 1 when in interactive mode, else 0
 */
int interactive(info_t *info)
{
        return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - this will checks if char is a delimeter
 * @c: char to be checked
 * @delim: expected delimeter string
 * Return: the expected return should be 1 if true, otherwise 0
 */
int is_delim(char c, char *delim)
{
        while (*delim)
                if (*delim++ == c)
                        return (1);
        return (0);
}

/**
 * _isalpha - this will checks for alphabetic char
 * @c: The char to inputed
 * Return: this should return 1 if c is alphabetic, else 0
 */

int _isalpha(int c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

/**
 * _atoi - to convert a string to an int
 * @s: the expected string that will be converted
 * Return: return 0 if there is no numbers in the string,
 * otherwise convert the number
 */

int _atoi(char *s)
{
        int j, sign = 1, flag = 0, output;
        unsigned int result = 0;

        for (j = 0; s[j] != '\0' && flag != 2; j++)
        {
                if (s[j] == '-')
                        sign *= -1;

                if (s[j] >= '0' && s[j] <= '9')
                {
                        flag = 1;
                        result *= 10;
                        result += (s[j] - '0');
                }
                else if (flag == 1)
                        flag = 2;
        }

        if (sign == -1)
                output = -result;
        else
                output = result;

        return (output);
}


2. builtin.c codes

#include "shell.h"

/**
 * _myexit - this will exit my shell
 * @info: this Structure holds possible arguments which is Used to keep
 * continous function prototype.
 * Return: exit with the specified exit status (0) for info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
        int exitcheck;

        if (info->argv[1]) /* If there is an exit arguement */
        {
                exitcheck = _erratoi(info->argv[1]);
                if (exitcheck == -1)
                {
                        info->status = 2;
                        print_error(info, "Illegal number: ");
                        _eputs(info->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                info->err_num = _erratoi(info->argv[1]);
                return (-2);
        }
        info->err_num = -1;
        return (-2);
}

/**
 * _mycd - the current directory of the process is modified
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype
 * Return: Always 0
 */
int _mycd(info_t *info)
{
        char *s, *dir, buffer[1024];
        int chdir_ret;

        s = getcwd(buffer, 1024);
        if (!s)
                _puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                dir = _getenv(info, "HOME=");
                if (!dir)
                        chdir_ret = /* TODO: what should this be? */
                                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
                else
                        chdir_ret = chdir(dir);
        }
        else if (_strcmp(info->argv[1], "-") == 0)
        {
                if (!_getenv(info, "OLDPWD="))
                {
                        _puts(s);
                        _putchar('\n');
                        return (1);
                }
                _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
                chdir_ret = /* TODO: what should this be? */
                        chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
        }
        else
                chdir_ret = chdir(info->argv[1]);
        if (chdir_ret == -1)
        {
                print_error(info, "can't cd to ");
                _eputs(info->argv[1]), _eputchar('\n');
        }
        else
        {
                _setenv(info, "OLDPWD", _getenv(info, "PWD="));
                _setenv(info, "PWD", getcwd(buffer, 1024));
        }
        return (0);
}

/**
 * _myhelp - modifications to the process's current directory
 * @info: Structure with potential arguments
 * used to preserve the constant function prototype.
 * Return: constant 0
 */
int _myhelp(info_t *info)
{
        char **arg_array;

        arg_array = info->argv;
        _puts("help call works. Function not yet implemented \n");
        if (0)
                _puts(*arg_array); /* temp att_unused workaround */
        return (0);
}



3. builtin1.c code

#include "shell.h"

/**
 * _myhistory - shows the history list, one command per line,
 * with line numbers starting at 0 before each command.
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype
 *  Return: constant 0.
 */
int _myhistory(info_t *info)
{
        print_list(info->history);
        return (0);
}

/**
 * unset_alias - changes alias to a string
 * @info: variable struct
 * @str: aliasing the string
 *
 * Return: 0 always on success and 1 for failure
 */
int unset_alias(info_t *info, char *str)
{
        char *p, c;
        int ret;

        p = _strchr(str, '=');
        if (!p)
                return (1);
        c = *p;
        *p = 0;
        ret = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *p = c;
        return (ret);
}

/**
 * set_alias - changes alias to a string
 * @info: variable struct
 * @str: aliasing the string
 *
 * Return:  0 always on success and 1 for failure
 */
int set_alias(info_t *info, char *str)
{
        char *p;

        p = _strchr(str, '=');
        if (!p)
                return (1);
        if (!*++p)
                return (unset_alias(info, str));

        unset_alias(info, str);
        return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - displays an alias string.
 * @node: an alias node
 *
 * Return: 0 always on success and 1 for failure
 */
int print_alias(list_t *node)
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _strchr(node->str, '=');
                for (a = node->str; a <= p; a++)
                _putchar(*a);
                _putchar('\'');
                _puts(p + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * _myalias - imitates the built-in alias (man alias)
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype.
 *  Return: constant 0
 */
int _myalias(info_t *info)
{
        int j = 0;
        char *p = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        print_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (j = 1; info->argv[j]; j++)
        {
                p = _strchr(info->argv[j], '=');
                if (p)
                        set_alias(info, info->argv[j]);
                else
                        print_alias(node_starts_with(info->alias, info->argv[j], '='));
        }

        return (0);
}


4. errors.c codes

#include "shell.h"

/**
 * _eputs - prints a string from the input
 * @str: a string that will be printed
 *
 * Return: 0.
 */
void _eputs(char *str)
{
        int j = 0;

        if (!str)
                return;
        while (str[j] != '\0')
        {
                _eputchar(str[j]);
                j++;
        }
}

/**
 * _eputchar - stderr is updated with the char c
 * @c: Printing the char
 *
 * Return: 1 is returned upon success, -1 upon failure,
 * and the appropriate value of erro is set.
 */
int _eputchar(char c)
{
        static int j;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
        {
                write(2, buf, j);
                j = 0;
        }
        if (c != BUF_FLUSH)
                buf[j++] = c;
        return (1);
}

/**
 * _putfd - puts a char c in the supplied fd
 * @c: Printing the char
 * @fd: The address to write to
 *
 * Return: 1 is returned upon success, -1 upon failure,
 * and the appropriate value of erro is set.
 */
int _putfd(char c, int fd)
{
        static int j;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
        {
                write(fd, buf, j);
                j = 0;
        }
        if (c != BUF_FLUSH)
                buf[j++] = c;
        return (1);
}

/**
 * _putsfd - displays a string of input
 * @str: a string that will be printed
 * @fd: The address to write to
 *
 * Return: the number of char entered
 */
int _putsfd(char *str, int fd)
{
        int j = 0;

        if (!str)
                return (0);
        while (*str)
        {
                j += _putfd(*str++, fd);
        }
        return (j);
}


5. errors1.c codes

#include "shell.h"

/**
 * _erratoi - translates a string into an integer.
 * @s: the string that needs to be converted
 * Return: 0 if there are no numbers in the string,
 * otherwise -1 in the event of an error
 *
 */
int _erratoi(char *s)
{
        int j = 0;
        unsigned long int result = 0;

        if (*s == '+')
                s++;  /* TODO: why does this make main return 255? */
        for (j = 0;  s[j] != '\0'; j++)
        {
                if (s[j] >= '0' && s[j] <= '9')
                {
                        result *= 10;
                        result += (s[j] - '0');
                        if (result > INT_MAX)
                                return (-1);
                }
                else
                        return (-1);
        }
        return (result);
}

/**
 * print_error - displays an error message
 * @info: the parameter and return information struct.
 * @estr: string with the indicated error type
 * Return: 0 if there are no numbers in the string,
 * otherwise -1 in the event of an error
 */
void print_error(info_t *info, char *estr)
{
        _eputs(info->fname);
        _eputs(": ");
        print_d(info->line_count, STDERR_FILENO);
        _eputs(": ");
        _eputs(info->argv[0]);
        _eputs(": ");
        _eputs(estr);
}

/**
 * print_d - function outputs an integer decimal number in base ten
 * @input: as input
 * @fd: writing to the filedescriptor
 *
 * Return: quantity of char printed
 */
int print_d(int input, int fd)
{
        int (*__putchar)(char) = _putchar;
        int j, count = 0;
        unsigned int _abs_, current;

        if (fd == STDERR_FILENO)
                __putchar = _eputchar;
        if (input < 0)
        {
                _abs_ = -input;
                __putchar('-');
                count++;
        }
        else
                _abs_ = input;
        current = _abs_;
        for (j = 1000000000; j > 1; j /= 10)
        {
                if (_abs_ / j)
                {
                        __putchar('0' + current / j);
                        count++;
                }
                current %= j;
        }
        __putchar('0' + current);
        count++;

        return (count);
}

/**
 * convert_number - a clone of itoa's converter function
 * @num: expected num
 * @base: the base
 * @flags: argument warnings
 *
 * Return: the string
 */
char *convert_number(long int num, int base, int flags)
{
        static char *array;
        static char buffer[50];
        char sign = 0;
        char *ptr;
        unsigned long n = num;

        if (!(flags & CONVERT_UNSIGNED) && num < 0)
        {
                n = -num;
                sign = '-';

        }
        array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        ptr = &buffer[49];
        *ptr = '\0';

        do      {
                *--ptr = array[n % base];
                n /= base;
        } while (n != 0);

        if (sign)
                *--ptr = sign;
        return (ptr);
}

/**
 * remove_comments - function substitutes "0" for the first occurence of "#"
 * @buf: address of the string that has to be changed
 *
 * Return: constant 0;
 */
void remove_comments(char *buf)
{
        int j;

        for (j = 0; buf[j] != '\0'; j++)
                if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
                {
                        buf[j] = '\0';
                        break;
                }
}


6. exits.c codes

#include "shell.h"

/**
 **_strncpy - duplicates a string
 *@dest: the string to copy to its final destination
 *@src: the original string
 *@n: the number of char that will be copied
 *Return: the string that is concatenated
 */
char *_strncpy(char *dest, char *src, int n)
{
        int j, k;
        char *s = dest;

        j = 0;
        while (src[j] != '\0' && j < n - 1)
        {
                dest[j] = src[j];
                j++;
        }
        if (j < n)
        {
                k = j;
                while (k < n)
                {
                        dest[k] = '\0';
                        k++;
                }
        }
        return (s);
}

/**
 **_strncat - two strings are concatenated
 *@dest: the initial string
 *@src: second string
 *@n: the maximum number of bytes to be used
 *Return: the string that has been concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
        int j, k;
        char *s = dest;

        j = 0;
        k = 0;
        while (dest[j] != '\0')
                j++;
        while (src[k] != '\0' && k < n)
        {
                dest[j] = src[k];
                j++;
                k++;
        }
        if (k < n)
                dest[j] = '\0';
        return (s);
}

/**
 **_strchr - finds a character within a string
 *@s: string that has to be parsed
 *@c: char to look for
 *Return: a pointer to the memory location s
 */
char *_strchr(char *s, char c)
{
        do {
                if (*s == c)
                        return (s);
        } while (*s++ != '\0');

        return (NULL);
}



7. getenv.c codes

#include "shell.h"

/**
 * get_environ - returns a duplicate of our environment's string array.
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype.
 * Return: constant 0
 */
char **get_environ(info_t *info)
{
        if (!info->environ || info->env_changed)
        {
                info->environ = list_to_strings(info->env);
                info->env_changed = 0;
        }

        return (info->environ);
}

/**
 * _unsetenv - Get rid of an environment variable
 * @info: SPotential argument-containing structure is employed
 * to keep the constant function prototype.
 *  Return: delete results in a 1; otherwise, a 0
 * @var: env var property for strings
 */
int _unsetenv(info_t *info, char *var)
{
        list_t *node = info->env;
        size_t j = 0;
        char *p;

        if (!node || !var)
                return (0);

        while (node)
        {
                p = starts_with(node->str, var);
                if (p && *p == '=')
                {
                        info->env_changed = delete_node_at_index(&(info->env), j);
                        j = 0;
                        node = info->env;
                        continue;
                }
                node = node->next;
                j++;
        }
        return (info->env_changed);
}

/**
 * _setenv - create a new environment variable from scratch,
 * or alter one that already exists
 * @info: Potential argument-containing structure. is employed
 * to keep the constant function prototype.
 * @var: env var property for strings
 * @value: the env var value string
 *  Return: constant 0
 */
int _setenv(info_t *info, char *var, char *value)
{
        char *buf = NULL;
        list_t *node;
        char *p;

        if (!var || !value)
                return (0);

        buf = malloc(_strlen(var) + _strlen(value) + 2);
        if (!buf)
                return (1);
        _strcpy(buf, var);
        _strcat(buf, "=");
        _strcat(buf, value);
        node = info->env;
        while (node)
        {
                p = starts_with(node->str, var);
                if (p && *p == '=')
                {
                        free(node->str);
                        node->str = buf;
                        info->env_changed = 1;
                        return (0);
                }
                node = node->next;
        }
        add_node_end(&(info->env), buf, 0);
        free(buf);
        info->env_changed = 1;
        return (0);
}



8. history.c codes

#include "shell.h"

/**
 * get_history_file - the history file is obtained
 * @info: variable struct
 *
 * Return: reserved string containing a history file
 */

char *get_history_file(info_t *info)
{
        char *buf, *dir;

        dir = _getenv(info, "HOME=");
        if (!dir)
                return (NULL);
        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
        if (!buf)
                return (NULL);
        buf[0] = 0;
        _strcpy(buf, dir);
        _strcat(buf, "/");
        _strcat(buf, HIST_FILE);
        return (buf);
}

/**
 * write_history - appends to an existing file or generates a new one
 * @info: this is the variable struct
 *
 * Return: 1 upon success, -1 otherwise
 */
int write_history(info_t *info)
{
        ssize_t fd;
        char *filename = get_history_file(info);
        list_t *node = NULL;

        if (!filename)
                return (-1);

        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fd == -1)
                return (-1);
        for (node = info->history; node; node = node->next)
        {
                _putsfd(node->str, fd);
                _putfd('\n', fd);
        }
        _putfd(BUF_FLUSH, fd);
        close(fd);
        return (1);
}

/**
 * read_history - file history to be read
 * @info: this is the variable struct
 *
 * Return: if successful, history count; otherwise, 0
 */
int read_history(info_t *info)
{
        int j, last = 0, linecount = 0;
        ssize_t fd, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = get_history_file(info);

        if (!filename)
                return (0);

        fd = open(filename, O_RDONLY);
        free(filename);
        if (fd == -1)
                return (0);
        if (!fstat(fd, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if (!buf)
                return (0);
        rdlen = read(fd, buf, fsize);
        buf[fsize] = 0;
        if (rdlen <= 0)
                return (free(buf), 0);
        close(fd);
        for (j = 0; j < fsize; j++)
                if (buf[j] == '\n')
                {
                        buf[j] = 0;
                        build_history_list(info, buf + last, linecount++);
                        last = j + 1;
                }
        if (last != j)
                build_history_list(info, buf + last, linecount++);
        free(buf);
        info->histcount = linecount;
        while (info->histcount-- >= HIST_MAX)
                delete_node_at_index(&(info->history), 0);
        renumber_history(info);
        return (info->histcount);
}

/**
 * build_history_list - creates a new entry in a history-linked list
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype.
 * @buf: buffer
 * @linecount: history linecount and history count
 *
 * Return: constant 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
        list_t *node = NULL;

        if (info->history)
                node = info->history;
        add_node_end(&node, buf, linecount);

        if (!info->history)
                info->history = node;
        return (0);
}

/**
 * renumber_history - the history linked list
 * is renumbered as modifications are made.
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype.
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
        list_t *node = info->history;
        int j = 0;

        while (node)
        {
                node->num = j++;
                node = node->next;
        }
        return (info->histcount = j);
}


9. lists.c codes

#include "shell.h"

/**
 * add_node - places a node at the beginning of the list.l
 * @head: the head node's pointer address
 * @str: node's str field
 * @num: used by history as a node index
 *
 * Return: the list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
        list_t *new_head;

        if (!head)
                return (NULL);
        new_head = malloc(sizeof(list_t));
        if (!new_head)
                return (NULL);
        _memset((void *)new_head, 0, sizeof(list_t));
        new_head->num = num;
        if (str)
        {
                new_head->str = _strdup(str);
                if (!new_head->str)
                {
                        free(new_head);
                        return (NULL);
                }
        }
        new_head->next = *head;
        *head = new_head;
        return (new_head);
}

/**
 * add_node_end - a node is added to the list's end.
 * @head: the head node's pointer address
 * @str: node's str field
 * @num: using history's node index
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
        list_t *new_node, *node;

        if (!head)
                return (NULL);

        node = *head;
        new_node = malloc(sizeof(list_t));
        if (!new_node)
                return (NULL);
        _memset((void *)new_node, 0, sizeof(list_t));
        new_node->num = num;
        if (str)
        {
                new_node->str = _strdup(str);
                if (!new_node->str)
                {
                        free(new_node);
                        return (NULL);
                }
        }
        if (node)
        {
                while (node->next)
                        node = node->next;
                node->next = new_node;
        }
        else
                *head = new_node;
        return (new_node);
}

/**
 * print_list_str - only print the str element from a linked list using list_t
 * @h: first node's pointer
 *
 * Return: the list size
 */
size_t print_list_str(const list_t *h)
{
        size_t j = 0;

        while (h)
        {
                _puts(h->str ? h->str : "(nil)");
                _puts("\n");
                h = h->next;
                j++;
        }
        return (j);
}

/**
 * delete_node_at_index - removes a node at a specified index.
 * @head: the initial node's address of the pointer
 * @index: index of the node to remove
 *
 * Return: 1 upon success and 0 upon failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
        list_t *node, *prev_node;
        unsigned int j = 0;

        if (!head || !*head)
                return (0);

        if (!index)
        {
                node = *head;
                *head = (*head)->next;
                free(node->str);
                free(node);
                return (1);
        }
        node = *head;
        while (node)
        {
                if (j == index)
                {
                        prev_node->next = node->next;
                        free(node->str);
                        free(node);
                        return (1);
                }
                j++;
                prev_node = node;
                node = node->next;
        }
        return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
        list_t *node, *next_node, *head;

        if (!head_ptr || !*head_ptr)
                return;
        head = *head_ptr;
        node = head;
        while (node)
        {
                next_node = node->next;
                free(node->str);
                free(node);
                node = next_node;
        }
        *head_ptr = NULL;
}


10. list1.c codes

#include "shell.h"

/**
 * list_len - specifies the linked list's length
 * @h: first node's pointer
 *
 * Return: the list size
 */
size_t list_len(const list_t *h)
{
        size_t j = 0;

        while (h)
        {
                h = h->next;
                j++;
        }
        return (j);
}

/**
 * list_to_strings - returns an array of strings using the list->str method.
 * @head: first node's pointer
 *
 * Return: strings array
 */
char **list_to_strings(list_t *head)
{
        list_t *node = head;
        size_t i = list_len(head), j;
        char **strs;
        char *str;

        if (!head || !i)
                return (NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if (!strs)
                return (NULL);
        for (i = 0; node; node = node->next, i++)
        {
                str = malloc(_strlen(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = _strcpy(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return (strs);
}


/**
 * print_list - prints every element of a list_t linked list.
 * @h: first node's pointer
 *
 * Return: the list size
 */
size_t print_list(const list_t *h)
{
        size_t j = 0;

        while (h)
        {
                _puts(convert_number(h->num, 10, 0));
                _putchar(':');
                _putchar(' ');
                _puts(h->str ? h->str : "(nil)");
                _puts("\n");
                h = h->next;
                j++;
        }
        return (j);
}

/**
 * node_starts_with - provides a node whose string contains the prefix.
 * @node: list head pointer
 * @prefix: string matching
 * @c: the char following prefix that will match
 *
 * Return: match null or nodes
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
        char *p = NULL;

        while (node)
        {
                p = starts_with(node->str, prefix);
                if (p && ((c == -1) || (*p == c)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}

/**
 * get_node_index - obtaining a node's index
 * @head: list head pointer
 * @node: pointer to the node
 *
 * Return: zero or the node's index
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
        size_t j = 0;

        while (head)
        {
                if (head == node)
                        return (j);
                head = head->next;
                j++;
        }
        return (-1);
}


11. parser.c codes

#include "shell.h"

/**
 * is_cmd - tests a file to see if it is an executable command
 * @info: struct information
 * @path: the file's location
 *
 * Return: if true 1, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
        struct stat st;

        (void)info;
        if (!path || stat(path, &st))
                return (0);

        if (st.st_mode & S_IFREG)
        {
                return (1);
        }
        return (0);
}

/**
 * dup_chars - chars with duplicate
 * @pathstr: the string path
 * @start: initial index
 * @stop: index for stopping
 *
 * Return: the new buffer pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
        static char buf[1024];
        int j = 0, k = 0;

        for (k = 0, j = start; j < stop; j++)
                if (pathstr[j] != ':')
                        buf[k++] = pathstr[j];
        buf[k] = 0;
        return (buf);
}

/**
 * find_path - identifies this command in the PATH string
 * @info: struct info
 * @pathstr: the string path
 * @cmd: locate the cmd
 *
 * Return: complete path of the command, if found, or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
        int j = 0, curr_pos = 0;
        char *path;

        if (!pathstr)
                return (NULL);
        if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
        {
                if (is_cmd(info, cmd))
                        return (cmd);
        }
        while (1)
        {
                if (!pathstr[j] || pathstr[j] == ':')
                {
                        path = dup_chars(pathstr, curr_pos, j);
                        if (!*path)
                                _strcat(path, cmd);
                        else
                        {
                                _strcat(path, "/");
                                _strcat(path, cmd);
                        }
                        if (is_cmd(info, path))
                                return (path);
                        if (!pathstr[j])
                                break;
                        curr_pos = j;
                }
                j++;
        }
        return (NULL);
}



12. string.c codes

#include "shell.h"

/**
 * _strlen - this returns the string length
 * @s: length of a string to be checked
 *
 * Return: the string length int
 */
int _strlen(char *s)
{
        int j = 0;

        if (!s)
                return (0);

        while (*s++)
                j++;
        return (j);
}

/**
 * _strcmp - compares the lexical patterns of two different languages.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
        while (*s1 && *s2)
        {
                if (*s1 != *s2)
                        return (*s1 - *s2);
                s1++;
                s2++;
        }
        if (*s1 == *s2)
                return (0);
        else
                return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - this checks  the needle starts with haystack
 * @haystack: the string to search
 * @needle: the sub_string to find
 *
 * Return: the address of next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
        while (*needle)
                if (*needle++ != *haystack++)
                        return (NULL);
        return ((char *)haystack);
}

/**
 * _strcat - this concatenates two strings
 * @dest: the buffer destination
 * @src: the buffer source
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
        char *ret = dest;

        while (*dest)
                dest++;
        while (*src)
                *dest++ = *src++;
        *dest = *src;
        return (ret);
}


13. string1.c

#include "shell.h"

/**
 * _strcpy - this copies a string
 * @dest: the string destination
 * @src: the string source
 *
 * Return: pointer string to destination
 */
char *_strcpy(char *dest, char *src)
{
        int j = 0;

        if (dest == src || src == 0)
                return (dest);
        while (src[j])
        {
                dest[j] = src[j];
                j++;
        }
        dest[j] = 0;
        return (dest);
}

/**
 * _strdup - the string is duplicated
 * @str: the duplicated string
 *
 * Return: a pointer to the duplicated string
 */
char *_strdup(const char *str)
{
        int length = 0;
        char *ret;

        if (str == NULL)
                return (NULL);
        while (*str++)
                length++;
        ret = malloc(sizeof(char) * (length + 1));
        if (!ret)
                return (NULL);
        for (length++; length--;)
                ret[length] = *--str;
        return (ret);
}

/**
 * _puts - an input string is printed
 * @str: the printed string
 *
 * Return: 0
 */
void _puts(char *str)
{
        int j = 0;

        if (!str)
                return;
        while (str[j] != '\0')
        {
                _putchar(str[j]);
                j++;
        }
}

/**
 * _putchar - this writes the char c to stdout
 * @c: The char to be printed
 *
 * Return: 1 On success
 * on failure, -1 is returned, and errno is appropriately set.
 */
int _putchar(char c)
{
        static int j;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
        {
                write(1, buf, j);
                j = 0;
        }
        if (c != BUF_FLUSH)
                buf[j++] = c;
        return (1);
}


14. tokenizer.c codes

#include "shell.h"

/**
 * **strtow - divides a string into words.
 * repeated delimiters are not taken into account.
 * @str: the string input
 * @d: the string delimeter
 * Return: a pointer to a string array, or NULL in the event of failure.
 */

char **strtow(char *str, char *d)
{
        int i, j, k, m, num_words = 0;
        char **s;

        if (str == NULL || str[0] == 0)
                return (NULL);
        if (!d)
                d = " ";
        for (i = 0; str[i] != '\0'; i++)
                if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
                        num_words++;

        if (num_words == 0)
                return (NULL);
        s = malloc((1 + num_words) * sizeof(char *));
        if (!s)
                return (NULL);
        for (i = 0, j = 0; j < num_words; j++)
        {
                while (is_delim(str[i], d))
                        i++;
                k = 0;
                while (!is_delim(str[i + k], d) && str[i + k])
                        k++;
                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j])
                {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        s[j][m] = str[i++];
                s[j][m] = 0;
        }
        s[j] = NULL;
        return (s);
}

/**
 * **strtow2 - divides a string into words.
 * @str: the string input
 * @d: the string delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
        int i, j, k, m, num_words = 0;
        char **s;

        if (str == NULL || str[0] == 0)
                return (NULL);
        for (i = 0; str[i] != '\0'; i++)
                if ((str[i] != d && str[i + 1] == d) ||
                                    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
                        num_words++;
        if (num_words == 0)
                return (NULL);
        s = malloc((1 + num_words) * sizeof(char *));
        if (!s)
                return (NULL);
        for (i = 0, j = 0; j < num_words; j++)
        {
                while (str[i] == d && str[i] != d)
                        i++;
                k = 0;
                while (str[i + k] != d && str[i + k] && str[i + k] != d)
                        k++;
                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j])
                {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }
                for (m = 0; m < k; m++)
                        s[j][m] = str[i++];
                s[j][m] = 0;
        }
        s[j] = NULL;
        return (s);
}


15. getline.c code

#include "shell.h"

/**
 * input_buf - chained commands with buffers
 * @info: variable struct
 * @buf: buffer's address
 * @len: address for Len Var
 *
 * Return: read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
        ssize_t s = 0;
        size_t len_p = 0;

        if (!*len) /* Fill the buffer if there is nothing left in it. */
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                s = getline(buf, &len_p, stdin);
#else
                s = _getline(info, buf, &len_p);
#endif
                if (s > 0)
                {
                        if ((*buf)[s - 1] == '\n')
                        {
                                (*buf)[s - 1] = '\0'; /* remove the trailing newline */
                                s--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';')) is this a command chain? */
                        {
                                *len = s;
                                info->cmd_buf = buf;
                        }
                }
        }
        return (s);
}

/**
 * get_input - eliminates the newline from a line.
 * @info: variable struct
 *
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
        static char *buf; /* the ';' command chain buffer */
        static size_t i, j, len;
        ssize_t r = 0;
        char **buf_p = &(info->arg), *p;

        _putchar(BUF_FLUSH);
        r = input_buf(info, &buf, &len);
        if (r == -1) /* EOF */
                return (-1);
        if (len) /* we have commands left in the chain buffer */
        {
                j = i; /* init new iterator to current buf position */
                p = buf + i; /* get pointer for return */

                check_chain(info, buf, &j, i, len);
                while (j < len) /* iterate to semicolon or end */
                {
                        if (is_chain(info, buf, &j))
                                break;
                        j++;
                }

                i = j + 1; /* increment past nulled ';'' */
                if (i >= len) /* reached end of buffer? */
                {
                        i = len = 0; /* reset position and length */
                        info->cmd_buf_type = CMD_NORM;
                }

                *buf_p = p; /* pass back pointer to current command position */
                return (_strlen(p)); /* return length of current command */
        }

        *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
        return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - a buffer is read
 * @info: variable struct
 * @buf: the buffer
 * @i: size
 *
 * Return: s
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
        ssize_t s = 0;

        if (*i)
                return (0);
        s = read(info->readfd, buf, READ_BUF_SIZE);
        if (s >= 0)
                *i = s;
        return (s);
}

/**
 * _getline - obtains the following line of input from STDIN
 * @info: variable struct
 * @ptr: address of a buffer pointer that is preallocated or NULL.
 * @length: if not NULL, the size of the preallocated ptr buffer.
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t i, len;
        size_t k;
        ssize_t r = 0, s = 0;
        char *p = NULL, *new_p = NULL, *c;

        p = *ptr;
        if (p && length)
                s = *length;
        if (i == len)
                i = len = 0;

        r = read_buf(info, buf, &len);
        if (r == -1 || (r == 0 && len == 0))
                return (-1);

        c = _strchr(buf + i, '\n');
        k = c ? 1 + (unsigned int)(c - buf) : len;
        new_p = _realloc(p, s, s ? s + k : k + 1);
        if (!new_p) /* MALLOC FAILURE! */
                return (p ? free(p), -1 : -1);

        if (s)
                _strncat(new_p, buf + i, k - i);
        else
                _strncpy(new_p, buf + i, k - i + 1);

        s += k - i;
        i = k;
        p = new_p;

        if (length)
                *length = s;
        *ptr = p;
        return (s);
}

/**
 * sigintHandler - ctrl-C blocks
 * @sig_num: the signal digit
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}



16. getinfo.c codes

#include "shell.h"

/**
 * clear_info - the info_t struct is initialized.
 * @info: address in struct
 */
void clear_info(info_t *info)
{
        info->arg = NULL;
        info->argv = NULL;
        info->path = NULL;
        info->argc = 0;
}

/**
 * set_info - the info_t struct is initialized.
 * @info: address in struct
 * @av: the argument vector
 */
void set_info(info_t *info, char **av)
{
        int j = 0;

        info->fname = av[0];
        if (info->arg)
        {
                info->argv = strtow(info->arg, " \t");
                if (!info->argv)
                {
                        info->argv = malloc(sizeof(char *) * 2);
                        if (info->argv)
                        {
                                info->argv[0] = _strdup(info->arg);
                                info->argv[1] = NULL;
                        }
                }
                for (j = 0; info->argv && info->argv[j]; j++)
                        ;
                info->argc = j;

                replace_alias(info);
                replace_vars(info);
        }
}

/**
 * free_info - releases info_t struct fields.
 * @info: the struct address
 * @all: true if all fields are freed
 */
void free_info(info_t *info, int all)
{
        ffree(info->argv);
        info->argv = NULL;
        info->path = NULL;
        if (all)
        {
                if (!info->cmd_buf)
                        free(info->arg);
                if (info->env)
                        free_list(&(info->env));
                if (info->history)
                        free_list(&(info->history));
                if (info->alias)
                        free_list(&(info->alias));
                ffree(info->environ);
                        info->environ = NULL;
                bfree((void **)info->cmd_buf);
                if (info->readfd > 2)
                        close(info->readfd);
                _putchar(BUF_FLUSH);
        }
}


17. memory.c code

#include "shell.h"

/**
 * bfree - releases a pointer and leaves the address empty.
 * @ptr: the pointer's address to freei
 *
 * Return: If liberated, 1; if not, 0
 */
int bfree(void **ptr)
{
        if (ptr && *ptr)
        {
                free(*ptr);
                *ptr = NULL;
                return (1);
        }
        return (0);
}



18. realloc.c code

#include "shell.h"

/**
 * _memset - gives memory a constant byte of data.
 * @s: the memory area's pointer
 * @b: bytes to be filled *s with
 * @n: the total number of bytes to be filled
 * Return: a pointer to the memory location s
 */
char *_memset(char *s, char b, unsigned int n)
{
        unsigned int j;

        for (j = 0; j < n; j++)
                s[j] = b;
        return (s);
}

/**
 * ffree - releases a group of strings
 * @pp: a group of strings
 */
void ffree(char **pp)
{
        char **a = pp;

        if (!pp)
                return;
        while (*pp)
                free(*pp++);
        free(a);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: the previous malloc'd block's pointer
 * @old_size: previous block's bytesize
 * @new_size: new block's byte size
 *
 * Return: pointing to the old block name.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
        char *p;

        if (!ptr)
                return (malloc(new_size));
        if (!new_size)
                return (free(ptr), NULL);
        if (new_size == old_size)
                return (ptr);

        p = malloc(new_size);
        if (!p)
                return (NULL);

        old_size = old_size < new_size ? old_size : new_size;
        while (old_size--)
                p[old_size] = ((char *)ptr)[old_size];
        free(ptr);
        return (p);
}



19. shell_loop.c codes

#include "shell.h"

/**
 * hsh - the main shell loop
 * @info: the variable & return struct info
 * @av: the vector argument from the main()
 *
 * Return: 0 on success, otherwise error code
 */
int hsh(info_t *info, char **av)
{
        ssize_t r = 0;
        int builtin_ret = 0;

        while (r != -1 && builtin_ret != -2)
        {
                clear_info(info);
                if (interactive(info))
                        _puts("$ ");
                _eputchar(BUF_FLUSH);
                r = get_input(info);
                if (r != -1)
                {
                        set_info(info, av);
                        builtin_ret = find_builtin(info);
                        if (builtin_ret == -1)
                                find_cmd(info);
                }
                else if (interactive(info))
                        _putchar('\n');
                free_info(info, 0);
        }
        write_history(info);
        free_info(info, 1);
        if (!interactive(info) && info->status)
                exit(info->status);
        if (builtin_ret == -2)
        {
                if (info->err_num == -1)
                        exit(info->status);
                exit(info->err_num);
        }
        return (builtin_ret);
}

/**
 * find_builtin - this finds a builtin cmd
 * @info: the variable & return info struct
 *
 * Return: if builtin not found -1,
 * for builtin executed successfully 0,
 * for builtin found but not successful 1,
 * for builtin signals exit() 2
 */
int find_builtin(info_t *info)
{
        int j, built_in_ret = -1;
        builtin_table builtintbl[] = {
                {"exit", _myexit},
                {"env", _myenv},
                {"help", _myhelp},
                {"history", _myhistory},
                {"setenv", _mysetenv},
                {"unsetenv", _myunsetenv},
                {"cd", _mycd},
                {"alias", _myalias},
                {NULL, NULL}
        };

        for (j = 0; builtintbl[j].type; j++)
                if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
                {
                        info->line_count++;
                        built_in_ret = builtintbl[j].func(info);
                        break;
                }
        return (built_in_ret);
}

/**
 * find_cmd - this finds a cmd in PATH
 * @info: the variable & return struct info
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
        char *path = NULL;
        int j, k;

        info->path = info->argv[0];
        if (info->linecount_flag == 1)
        {
                info->line_count++;
                info->linecount_flag = 0;
        }
        for (j = 0, k = 0; info->arg[j]; j++)
                if (!is_delim(info->arg[j], " \t\n"))
                        k++;
        if (!k)
                return;

        path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
        if (path)
        {
                info->path = path;
                fork_cmd(info);
        }
        else
        {
                if ((interactive(info) || _getenv(info, "PATH=")
                                        || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
                        fork_cmd(info);
                else if (*(info->arg) != '\n')
                {
                        info->status = 127;
                        print_error(info, "not found\n");
                }
        }
}

/**
 * fork_cmd - the forks a an exec thread to run cmd
 * @info: the variable & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                /* TODO: PUT ERROR FUNCTION */
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(info->path, info->argv, get_environ(info)) == -1)
                {
                        free_info(info, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
                /* TODO: PUT ERROR FUNCTION */
        }
        else
        {
                wait(&(info->status));
                if (WIFEXITED(info->status))
                {
                        info->status = WEXITSTATUS(info->status);
                        if (info->status == 126)
                                print_error(info, "Permission denied\n");
                }
        }
}



20. vars.c codes

#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
        size_t j = *p;

        if (buf[j] == '|' && buf[j + 1] == '|')
        {
                buf[j] = 0;
                j++;
                info->cmd_buf_type = CMD_OR;
        }
        else if (buf[j] == '&' && buf[j + 1] == '&')
        {
                buf[j] = 0;
                j++;
                info->cmd_buf_type = CMD_AND;
        }
        else if (buf[j] == ';') /* found end of this command */
        {
                buf[j] = 0; /* replace semicolon with null */
                info->cmd_buf_type = CMD_CHAIN;
        }
        else
                return (0);
        *p = j;
        return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (info->cmd_buf_type == CMD_AND)
        {
                if (info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }
        if (info->cmd_buf_type == CMD_OR)
        {
                if (!info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }

        *p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
        int i;
        list_t *node;
        char *p;

        for (i = 0; i < 10; i++)
        {
                node = node_starts_with(info->alias, info->argv[0], '=');
                if (!node)
                        return (0);
                free(info->argv[0]);
                p = _strchr(node->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
                if (!p)
                        return (0);
                info->argv[0] = p;
        }
        return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
        int i = 0;
        list_t *node;

        for (i = 0; info->argv[i]; i++)
        {
                if (info->argv[i][0] != '$' || !info->argv[i][1])
                        continue;

                if (!_strcmp(info->argv[i], "$?"))
                {
                        replace_string(&(info->argv[i]),
                                        _strdup(convert_number(info->status, 10, 0)));
                        continue;
                }
                if (!_strcmp(info->argv[i], "$$"))
                {
                        replace_string(&(info->argv[i]),
                                        _strdup(convert_number(getpid(), 10, 0)));
                        continue;
                }
                node = node_starts_with(info->env, &info->argv[i][1], '=');
                if (node)
                {
                        replace_string(&(info->argv[i]),
                                        _strdup(_strchr(node->str, '=') + 1));
                        continue;
                }
                replace_string(&info->argv[i], _strdup(""));

        }
        return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
        free(*old);
        *old = new;
        return (1);
}



21. main.c codes

#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
        info_t info[] = { INFO_INIT };
        int fd = 2;

        asm ("mov %1, %0\n\t"
                        "add $3, %0"
                        : "=r" (fd)
                        : "r" (fd));

        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(av[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(av[1]);
                                _eputchar('\n');
                                _eputchar(BUF_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                info->readfd = fd;
        }
        populate_env_list(info);
        read_history(info);
        hsh(info, av);
        return (EXIT_SUCCESS);
}



22. shell.c codes

#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr -the singly linked list
 * @num: number field
 * @str: the string
 * @next: this points to the next node
 */
typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - contains fictitious arg that can be used
 * as input to a function,
 * providing a common prototype for function pointer structs.
 * @arg: a string produced by getline that contains arguments
 * @argv: a collection of strings created from arg
 * @path: the path in a string for the current command
 * @argc: the arg count
 * @line_count: this is the error count
 * @err_num: this is the error code for exit()s
 * @linecount_flag: count this line of input if on
 * @fname: this is the program filename
 * @env: localized linked list copy of enviroment
 * @environ: LL env environment updated specifically
 * @history: this is the history node
 * @alias: alias node
 * @env_changed: if environ was changed on
 * @status: the last command that was executed's return status
 * @cmd_buf: pointer to cmd_buf's address, if chaining
 * @cmd_buf_type: cmd_type ||, &&, ;
 * @readfd: the fd to read line input from
 * @histcount: counting the amount of historical lines
 */
typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf; /* pointer to cmd ; chain buff, for memory mangement */
        int cmd_buf_type; /* CMD_type ||, &&, ; */
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                0, 0, 0}

/**
 * struct builtin - this contains a builtin string and related function
 * @type: this is the builtin command flag
 * @func: this is the function
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;

/* lists.c functions*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c functions*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* parser.c functions*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c function*/
int loophsh(char **);

/* errors.c functions*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c functions*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c functions*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* atoi.c functions*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c functions*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c functions*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin1.c functions*/
int _myhistory(info_t *);
int _myalias(info_t *);

/* exits.c functions*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c functions*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c functions*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c function*/
int bfree(void **);

/* getline.c functions*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c functions*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c functions*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c functions*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c function*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* vars.c functions*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* shloop.c functions*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

#endif




README.md

#this is a group project on simple shell

the task for this project are stated as follows:

#0. Write a beautiful code that passes the Betty checks
#1. Write a UNIX command line interpreter.
#2. Write a UNIX command line interpreter.
#3. Handle command lines with arguments
#4. Handle the PATH
#5. Implement the exit built-in, that exits the shell
#6. Implement the env built-in, that prints the current environment
#7. Write your own getline function
#8. You are not allowed to use strtok
#9. Handle arguments for the built-in exit
#10.Implement the setenv and unsetenv builtin commands
#11.Implement the builtin command
#12.Handle the commands separato
#13.Handle the && and || shell logical operators
#14.Implement the alias builtin command
#15.Handle comments
#16. File as input

Here is a brief description of each functions used in each files that make up the simple shell:

#1. _atoi.c file

1. `int interactive(info_t *info)`
   - This function checks if the program is being run in an interactive mode (like a user typing commands in a terminal).
   - It returns `1` if it's interactive, and `0` if it's not.

2. `int is_delim(char c, char *delim)`
   - This function checks if a given character `c` is one of the delimiter characters in a provided string.
   - It returns `1` if `c` is a delimiter, and `0` if it's not.

3. `int _isalpha(int c)`
   - This function checks if a character `c` is a letter of the alphabet (either uppercase or lowercase).
   - It returns `1` if `c` is a letter, and `0` if it's not.

4. `int _atoi(char *s)`
   - This function converts a string of digits into an integer.
   - It returns the integer value represented by the string.
   - If the string doesn't contain any numbers, it returns `0`.
   - It handles negative numbers and converts positive and negative numeric strings into integers.

#2. builtin.c file

1. `_myexit(info_t *info)`
   - This function handles the "exit" command for a shell.
   - If there's an argument (e.g., `exit 123`), it tries to convert the argument to an integer and set it as the exit status.
   - If the argument is not a valid number, it prints an error message.
   - If there's no argument, it sets the exit status to -1.
   - It returns -2 to indicate that the shell should exit.

2. `_mycd(info_t *info)`
   - This function handles the "cd" (change directory) command for a shell.
   - If there's no argument, it tries to change the directory to the user's home directory (retrieved from the "HOME" environment variable).
   - If the argument is "-", it tries to change to the previous directory (retrieved from the "OLDPWD" environment variable).
   - Otherwise, it tries to change to the directory specified in the argument.
   - It updates the "PWD" and "OLDPWD" environment variables accordingly.
   - If the directory change fails, it prints an error message.

3. `_myhelp(info_t *info)`
   - This function is intended to handle the "help" command for a shell, but it's currently not implemented.
   - It prints a message indicating that the function is not yet implemented.
   - It always returns 0.

#3. builtin1.c file

1. `_myhistory(info_t *info)`
   - This function is responsible for displaying a history list of previously entered commands.
   - It prints each command with a line number, starting from 0.
   - It takes a structure `info` as a parameter but doesn't seem to use it.
   - It returns 0, indicating successful execution.

2. `int unset_alias(info_t *info, char *str)`
   - This function is used to remove an alias (a custom command) from the shell.
   - It takes the `info` structure and a string `str` as parameters.
   - It looks for an equal sign ('=') in the string and deletes the alias accordingly.
   - It returns 0 on success and 1 on failure.

3. `int set_alias(info_t *info, char *str)`
   - This function sets an alias (a custom command) in the shell.
   - It takes the `info` structure and a string `str` as parameters.
   - It first checks if an alias with the same name already exists and removes it if it does.
   - Then, it adds the new alias to the list.
   - It returns 0 on success and 1 on failure.

4. `int print_alias(list_t *node)`
   - This function prints an alias stored in a linked list.
   - It takes a node from the linked list as a parameter.
   - It extracts and prints the alias.
   - It returns 0 on success and 1 on failure.

5. `_myalias(info_t *info)`
   - This function emulates the built-in `alias` command in a shell.
   - If called without arguments, it lists all defined aliases.
   - If called with arguments in the form of "alias_name=command," it sets or updates aliases.
   - It takes the `info` structure as a parameter.
   - It returns 0, indicating successful execution.

#4. environ.c file

1. `_myenv(info_t *info)`
   - This function is responsible for printing the environment variables.
   - It takes the `info` structure as a parameter but doesn't seem to use it.
   - It prints a list of environment variables.
   - It returns 0, indicating successful execution.

2. `char *_getenv(info_t *info, const char *name)`
   - This function is used to retrieve the value of an environment variable by its name.
   - It takes the `info` structure and the name of the environment variable as parameters.
   - It searches through the list of environment variables and returns the value of the specified variable.
   - If the variable is not found, it returns NULL.

3. `_mysetenv(info_t *info)`
   - This function is used to set or modify an environment variable.
   - It takes the `info` structure as a parameter.
   - It expects exactly three arguments: the command name, the name of the variable, and its value.
   - If the number of arguments is incorrect, it prints an error message and returns 1.
   - Otherwise, it sets or updates the specified environment variable and returns 0.

4. `_myunsetenv(info_t *info)`
   - This function is used to unset (remove) one or more environment variables.
   - It takes the `info` structure as a parameter.
   - It expects one or more arguments, each specifying the name of an environment variable to unset.
   - If no arguments are provided, it prints an error message and returns 1.
   - It unsets (removes) the specified environment variables and returns 0.

5. `int populate_env_list(info_t *info)`
   - This function is used to populate a linked list with environment variables.
   - It takes the `info` structure as a parameter.
   - It iterates through the global `environ` array (which contains environment variable strings) and adds each variable to a linked list.
   - It assigns the resulting linked list to `info->env`.
   - It returns 0, indicating successful execution.

#5. errors.c file

1. `_eputs(char *str)`
   - This function is responsible for printing a string to the standard error stream (stderr).
   - It takes a character pointer `str` as a parameter, which is the string to be printed.
   - It iterates through the characters in the string and prints each character to stderr.
   - It returns `void` (no return value).

2. `_eputchar(char c)`
   - This function is responsible for printing a single character to the standard error stream (stderr).
   - It takes a character `c` as a parameter, which is the character to be printed.
   - It stores characters in a buffer until it's full or until a special character (BUF_FLUSH) is encountered.
   - When the buffer is full or when BUF_FLUSH is encountered, it writes the buffered characters to stderr.
   - It returns `1` upon successful printing, `-1` upon failure, and sets the appropriate error value.

3. `_putfd(char c, int fd)`
   - This function is similar to `_eputchar`, but it allows printing a character to a specified file descriptor (`fd`) rather than just stderr.
   - It also uses a buffer to store characters and flushes the buffer when it's full or when BUF_FLUSH is encountered.
   - It returns `1` upon successful printing, `-1` upon failure, and sets the appropriate error value.

4. `_putsfd(char *str, int fd)`
   - This function is similar to `_eputs`, but it allows printing a string to a specified file descriptor (`fd`) rather than just stderr.
   - It takes a character pointer `str` as a parameter, which is the string to be printed, and an integer `fd` as the file descriptor to which the string is printed.
   - It iterates through the characters in the string and uses `_putfd` to print each character to the specified file descriptor.
   - It returns the total number of characters printed.

#6. errors1.c file

1. `_erratoi(char *s)`
   - This function converts a string into an integer.
   - It takes a character pointer `s` as input.
   - It handles positive and negative numbers and checks for overflow.
   - If the conversion is successful, it returns the integer value.
   - If the input string is not a valid number or overflows, it returns -1.

2. `print_error(info_t *info, char *estr)`
   - This function prints an error message to the standard error stream (stderr).
   - It takes an `info_t` structure pointer `info` and an error message string `estr`.
   - It prints the program name, line number, and error message to stderr.

3. `print_d(int input, int fd)`
   - This function prints an integer in decimal format to the specified file descriptor (`fd`).
   - It takes an integer `input` and an integer `fd` as input.
   - It handles both positive and negative integers and returns the number of characters printed.

4. `char *convert_number(long int num, int base, int flags)`
   - This function converts a number into a string representation in a given base.
   - It takes a long integer `num`, an integer `base` (e.g., 10 for decimal), and flags.
   - It handles both signed and unsigned numbers and supports converting to lowercase or uppercase representations.
   - It returns a pointer to the string representation of the number.

5. `remove_comments(char *buf)`
   - This function removes comments from a string by replacing the first occurrence of '#' with a null terminator.
   - It takes a character pointer `buf` as input and modifies the string in place.
   - It replaces the '#' character with '\0' to effectively remove everything after the '#' symbol.

#7. exits.c file

1. `_strncpy(char *dest, char *src, int n)`
   - This function duplicates part of a string.
   - It takes three parameters: `dest` (the destination string), `src` (the source string), and `n` (the maximum number of characters to copy).
   - It copies up to `n` characters from `src` to `dest` and returns a pointer to `dest`.
   - If the length of `src` is less than `n`, it pads the remaining space in `dest` with null characters.

2. `_strncat(char *dest, char *src, int n)`
   - This function concatenates two strings.
   - It takes three parameters: `dest` (the initial string), `src` (the second string to append), and `n` (the maximum number of characters to use from `src`).
   - It appends up to `n` characters from `src` to the end of `dest`.
   - It returns a pointer to the modified `dest` string.
   - If the length of `src` is less than `n`, it ensures that `dest` is null-terminated.

3. `_strchr(char *s, char c)`
   - This function finds the first occurrence of a character `c` within a string `s`.
   - It takes two parameters: `s` (the string to search within) and `c` (the character to look for).
   - It iterates through the characters in `s` until it finds `c` or reaches the end of the string.
   - If it finds `c`, it returns a pointer to the memory location of `c` within the string `s`.
   - If `c` is not found in `s`, it returns `NULL`.

#8. getline.c file

1. `ssize_t input_buf(info_t *info, char **buf, size_t *len)`
   - This function reads input from the user, handles command chains separated by semicolons, and builds a history list.
   - It takes an `info_t` structure pointer `info`, a pointer to a character pointer `buf`, and a pointer to a size_t `len`.
   - It checks if there is any input left in the buffer. If not, it reads a line of input from the user and handles it.
   - It removes trailing newline characters and comments from the input.
   - If the input contains semicolons, indicating a command chain, it stores the remaining input in the buffer.
   - It updates the `len` parameter with the length of the input.
   - It returns the number of bytes read.

2. `ssize_t get_input(info_t *info)`
   - This function manages input for the shell, including handling command chains.
   - It keeps track of the current position in the input buffer.
   - If there are commands left in the buffer from a previous input, it retrieves and processes them.
   - If not, it reads a new line of input and prepares it for processing.
   - It returns the number of characters in the current command.

3. `ssize_t read_buf(info_t *info, char *buf, size_t *i)`
   - This function reads data from a file descriptor (`info->readfd`) into a buffer.
   - It takes an `info_t` structure pointer `info`, a character pointer `buf`, and a pointer to a size_t `i`.
   - If there is data left in the buffer, it doesn't read more and returns 0.
   - If the buffer is empty, it reads data from the file descriptor and updates `i` with the number of bytes read.
   - It returns the number of bytes read or 0 if the buffer still contains data.

4. `int _getline(info_t *info, char **ptr, size_t *length)`
   - This function reads a line of input from the user or a file descriptor into a dynamically allocated buffer.
   - It takes an `info_t` structure pointer `info`, a pointer to a character pointer `ptr`, and a pointer to a size_t `length`.
   - It reads input in chunks, concatenates it into a larger buffer, and reallocates memory as needed.
   - It returns the total number of characters read, or -1 in case of an error or EOF.

5. `void sigintHandler(int sig_num)`
   - This function handles the SIGINT signal (Ctrl-C) by printing a newline and a shell prompt.
   - It takes the signal number `sig_num` as a parameter, which is unused.
   - It prints a newline and a shell prompt, allowing the user to enter a new command.

#9. getenv.c file

1. `char **get_environ(info_t *info)`
   - This function returns a duplicate of the shell's environment variables as a string array.
   - It takes an `info_t` structure pointer `info`.
   - If the `environ` variable is empty or if the environment has changed, it converts the linked list of environment variables (`info->env`) into a string array and updates the `environ` variable.
   - It returns the string array of environment variables.

2. `int _unsetenv(info_t *info, char *var)`
   - This function removes an environment variable.
   - It takes an `info_t` structure pointer `info` and a string `var` representing the environment variable to be removed.
   - It iterates through the linked list of environment variables and looks for a variable that starts with `var` followed by an equal sign (`=`).
   - If found, it deletes the node containing that variable.
   - It returns 1 if the environment was changed (a variable was deleted), otherwise 0.

3. `int _setenv(info_t *info, char *var, char *value)`
   - This function creates a new environment variable or modifies an existing one.
   - It takes an `info_t` structure pointer `info`, a string `var` representing the environment variable name, and a string `value` representing its value.
   - It allocates memory for a new string in the format "var=value".
   - It checks if the variable already exists in the linked list of environment variables (`info->env`).
   - If it exists, it updates the value of the existing variable.
   - If it doesn't exist, it adds the new variable to the end of the linked list.
   - It sets the `env_changed` flag to 1 to indicate that the environment has been modified.
   - It returns 0.

#10. getinfo.c file

1. `void clear_info(info_t *info)`
   - This function initializes the fields of the `info_t` struct to their default values or NULL.
   - It takes an `info_t` structure pointer `info` as input.
   - It sets the following fields to NULL or zero: `arg`, `argv`, `path`, and `argc`.

2. `void set_info(info_t *info, char **av)`
   - This function initializes the `info_t` struct with information from the command line arguments.
   - It takes an `info_t` structure pointer `info` and a string array `av` representing the command line arguments.
   - It sets the `fname` field of `info` to the first element of `av`, which is typically the name of the shell program.
   - It processes the `arg` field (a string containing the command line input) to split it into an array of individual arguments stored in `argv`.
   - It calculates the number of arguments (`argc`) in `argv`.
   - It may perform additional operations like replacing aliases and environment variables in the arguments.

3. `void free_info(info_t *info, int all)`
   - This function releases memory allocated for fields within the `info_t` struct.
   - It takes an `info_t` structure pointer `info` and an integer `all` as input.
   - It frees the memory associated with the `argv` field, sets it to NULL, and also sets the `path` field to NULL.
   - If `all` is true, it performs additional cleanup, such as freeing memory for the `arg` field, linked lists (`env`, `history`, `alias`), and the `environ` string array.
   - It closes the file descriptor `readfd` if it is greater than 2 (indicating that it's not a standard input/output/error stream).
   - Finally, it flushes the standard output buffer.

#11. history.c file

1. `char *get_history_file(info_t *info)`
   - This function returns a string containing the path to the history file.
   - It constructs the path using the user's home directory obtained from the environment variable "HOME" and appends the name of the history file (defined as `HIST_FILE`).
   - Returns the history file path as a dynamically allocated string.

2. `int write_history(info_t *info)`
   - This function appends the command history to a history file.
   - It opens the history file (retrieved using `get_history_file`) in write mode and writes each command from the `info->history` linked list to the file.
   - Returns 1 upon success or -1 on failure.

3. `int read_history(info_t *info)`
   - This function reads the command history from a history file.
   - It opens the history file (retrieved using `get_history_file`) in read-only mode and reads the contents into a buffer.
   - The function then parses the buffer, splitting it into individual commands, and builds a linked list (`info->history`) to store the command history.
   - Returns the count of history items read or 0 if there was an issue reading the history file.

4. `int build_history_list(info_t *info, char *buf, int linecount)`
   - This function creates a new entry in the history linked list for a command.
   - It takes the command string `buf` and the linecount as input and adds a new node to the `info->history` linked list, storing the command and its linecount.
   - Returns 0 on success.

5. `int renumber_history(info_t *info)`
   - This function renumbers the history linked list after modifications.
   - It iterates through the `info->history` linked list and assigns new linecount values to each node, ensuring they are in sequential order.
   - Returns the new `histcount` (total number of history items).

#12. lists.c file

1. `list_t *add_node(list_t **head, const char *str, int num)`
   - This function adds a new node at the beginning of the linked list.
   - `head` is a pointer to the head of the list, `str` is the string to be stored in the new node, and `num` is used as a node index.
   - It returns a pointer to the new head of the list.

2. `list_t *add_node_end(list_t **head, const char *str, int num)`
   - This function adds a new node at the end of the linked list.
   - `head` is a pointer to the head of the list, `str` is the string to be stored in the new node, and `num` is used as a node index.
   - It returns a pointer to the new node added at the end.

3. `size_t print_list_str(const list_t *h)`
   - This function prints the `str` element of each node in the linked list.
   - It takes the head of the list `h` as input and prints each node's `str` value.
   - It returns the size of the list (number of nodes).

4. `int delete_node_at_index(list_t **head, unsigned int index)`
   - This function deletes a node at a specified index in the linked list.
   - `head` is a pointer to the head of the list, and `index` is the index of the node to be deleted.
   - It returns 1 upon successful deletion and 0 upon failure.

5. `void free_list(list_t **head_ptr)`
   - This function frees all nodes in the linked list and sets the `head_ptr` to NULL.
   - It takes a pointer to the pointer of the head node as input and frees all nodes in the list.

#13 list1.c file

1. `size_t list_len(const list_t *h)`
   - This function returns the length (number of nodes) of a linked list.
   - It takes the head of the list `h` as input.
   - It iterates through the list and counts the nodes, returning the count.

2. `char **list_to_strings(list_t *head)`
   - This function converts a linked list of strings into an array of strings.
   - It takes the head of the list `head` as input.
   - It allocates memory for an array of strings and copies each node's `str` value into the array.
   - It returns the array of strings. The last element of the array is set to NULL.

3. `size_t print_list(const list_t *h)`
   - This function prints each element of a linked list along with its index.
   - It takes the head of the list `h` as input.
   - It iterates through the list, printing each node's index, `str` value, and a newline.
   - It returns the count of printed nodes.

4. `list_t *node_starts_with(list_t *node, char *prefix, char c)`
   - This function searches for a node in the linked list whose `str` value starts with the specified `prefix`.
   - Optionally, it can match a specific character `c` after the prefix.
   - It returns a pointer to the first matching node found or NULL if no match is found.

5. `ssize_t get_node_index(list_t *head, list_t *node)`
   - This function returns the index (position) of a given node in the linked list.
   - It takes the head of the list `head` and a pointer to the target node `node` as input.
   - It iterates through the list to find the target node and returns its index. If the node is not found, it returns -1.

#14. memory.c file

The `bfree` function is a simple utility function for freeing a dynamically allocated memory block and setting the pointer to `NULL`. Here's a breakdown of the function:

- `int bfree(void **ptr)`: This function takes a pointer to a pointer (`**ptr`) as its parameter. This allows it to modify the original pointer (set it to `NULL`) after freeing the memory it points to.

- Inside the function, it checks whether the passed pointer `ptr` is not `NULL` and whether the memory it points to (`*ptr`) is not `NULL`.

- If both conditions are met, it proceeds to free the memory block pointed to by `*ptr` using the `free` function from the C standard library.

- After freeing the memory, it sets the original pointer `*ptr` to `NULL`.

- Finally, the function returns `1` to indicate that memory was successfully freed, or `0` if either `ptr` or `*ptr` was `NULL` (no action was taken).

#15. parser.c file

1. `is_cmd`:
   - This function checks if a given file path corresponds to an executable command.
   - It takes two parameters: `info` (a structure containing information, although it's not used in this function) and `path` (the file's location).
   - It uses the `stat` function to check if the file exists and retrieves its status.
   - If the file exists and is a regular file (S_IFREG), the function returns `1`, indicating that it's an executable command. Otherwise, it returns `0`.

2. `dup_chars`:
   - This function duplicates characters from a string within a specified range and returns the result as a new string.
   - It takes three parameters: `pathstr` (the string path), `start` (the initial index to start duplicating characters), and `stop` (the index to stop duplicating characters).
   - It uses a static character buffer `buf` to store the duplicated characters.
   - It iterates through the characters in `pathstr` between `start` and `stop-1` and copies them to `buf`, excluding colons `':'`.
   - The result is null-terminated, and `buf` is returned as a new string.

3. `find_path`:
   - This function identifies the complete path of a command within a colon-separated PATH string.
   - It takes three parameters: `info` (a structure containing information, although it's not used in this function), `pathstr` (the PATH string containing directory paths separated by colons), and `cmd` (the command to locate within the PATH).
   - It first checks if `cmd` starts with `"./"`, which indicates a relative path to the current directory. If it starts with "./" and is an executable command (`is_cmd` function), it returns `cmd` as it is already the full path.
   - If not, it iterates through the characters in `pathstr`, breaking it into individual path segments separated by colons.
   - For each path segment, it appends `cmd` to the end and checks if the resulting path is an executable command using the `is_cmd` function.
   - If it finds an executable command, it returns the complete path. If no path segments contain an executable command, it returns `NULL`.

#16. ralloc.c file

1. `_memset`:
   - This function fills a block of memory with a specified byte value.
   - It takes three parameters: `s` (a pointer to the memory area), `b` (the byte value to fill with), and `n` (the number of bytes to fill).
   - It loops through the memory area and sets each byte to the specified value `b`.
   - Finally, it returns the same pointer `s` to the filled memory area.

2. `ffree`:
   - This function is used to free a group of strings (an array of strings).
   - It takes a parameter `pp`, which is a pointer to an array of strings.
   - It first checks if `pp` is not NULL (if it's NULL, it does nothing).
   - Then, it iterates through the array of strings and frees each individual string using the `free` function.
   - After freeing all the strings, it frees the pointer `pp` itself, which was pointing to the array of strings.

3. `_realloc`:
   - This function reallocates memory for a previously allocated block.
   - It takes three parameters: `ptr` (a pointer to the previously allocated block of memory), `old_size` (the size of the old block in bytes), and `new_size` (the size of the new block in bytes).
   - If `ptr` is NULL, it behaves like `malloc` and allocates a new block of memory of size `new_size`.
   - If `new_size` is 0, it deallocates the old block pointed to by `ptr` and returns NULL.
   - If `new_size` is equal to `old_size`, it returns `ptr` as no reallocation is needed.
   - If the new size is different from the old size, it allocates a new block of memory of size `new_size`, copies the content from the old block to the new block, and then frees the old block using `free`.
   - Finally, it returns a pointer to the new block of memory.

In simpler terms, these functions are used for memory operations:
- `_memset` fills a chunk of memory with a specific value.
- `ffree` frees memory associated with an array of strings.
- `_realloc` changes the size of a memory block, copying data if necessary, and frees the old block.

#17. shell_loop file

1. `hsh` Function:
   - This is the main function for the shell.
   - It contains a loop that repeatedly executes commands until either an error occurs or the user decides to exit.
   - Inside the loop:
     - Clears the information related to the previous command.
     - If in interactive mode (running in a terminal), it displays a command prompt (`$ `).
     - Reads user input.
     - Processes and interprets the input:
       - Sets up information about the command, arguments, and environment variables.
       - Checks if the input corresponds to a built-in command (e.g., `exit`, `env`) and executes it if found.
       - If not a built-in command, it tries to find and execute an external command.
     - Finally, it frees the allocated memory for the command information.
   - After the loop, it writes the command history to a file, frees any remaining memory, and exits.

2. `find_builtin` Function:
   - This function looks for and executes built-in shell commands.
   - It compares the user's input (the first word) with a list of known built-in commands.
   - If a match is found, it executes the corresponding built-in function.
   - Returns values based on the outcome of executing the built-in command.

3. `find_cmd` Function:
   - This function is responsible for finding and executing external commands (commands not built into the shell).
   - It first checks if the input contains non-whitespace characters to determine if a command exists.
   - Then, it attempts to find the command in directories listed in the `PATH` environment variable.
   - If found, it sets the path to the command, and later the `fork_cmd` function is called to execute the command.
   - If not found, it checks if the input starts with '/' (indicating an absolute path) or if the command exists without a specified path. If so, it calls `fork_cmd` to execute the command.
   - If none of the above conditions are met, it indicates that the command was not found.

4. `fork_cmd` Function:
   - This function is responsible for creating a new process (child process) to execute an external command.
   - It uses the `fork()` system call to create a new process.
   - In the child process, it attempts to execute the command using `execve()` and the path to the command.
   - If the execution is successful, the child process runs the command, and the parent process waits for it to complete.
   - If there is an error, it handles permission errors and reports them.

#18. string.c file
Here's a simplified explanation of this code:

1. `_strlen` Function:
   - Calculates and returns the length of a given string (`s`).
   - It counts the number of characters in the string until it reaches the null terminator (`'\0'`).
   - Returns an integer representing the length of the string.

2. `_strcmp` Function:
   - Compares two strings (`s1` and `s2`) lexically, character by character.
   - It returns a negative value if `s1` is less than `s2`, a positive value if `s1` is greater than `s2`, and zero if they are equal.
   - This function is used to determine the order of strings in lexicographical order.

3. `starts_with` Function:
   - Checks if a given string (`haystack`) starts with a specified substring (`needle`).
   - It iterates through both strings, character by character, comparing them.
   - If `needle` is found at the beginning of `haystack`, it returns a pointer to the character in `haystack` right after the matched portion. Otherwise, it returns `NULL`.

4. `_strcat` Function:
   - Concatenates (appends) one string (`src`) to the end of another string (`dest`).
   - It iterates through `dest` until it reaches the null terminator, indicating the end of `dest`. Then, it appends the characters from `src` to `dest`.
   - The function returns a pointer to the modified `dest` string.

#19. string1.c file

1. `_strcpy` Function:
   - Copies a source string (`src`) into a destination string (`dest`).
   - Iterates through the characters of the source string and copies them one by one into the destination string until it encounters the null terminator (`'\0'`), indicating the end of the string.
   - Returns a pointer to the destination string (`dest`).

2. `_strdup` Function:
   - Duplicates a given string (`str`).
   - Calculates the length of the input string and allocates memory for a new string of the same length.
   - Copies the characters from the input string to the new string.
   - Returns a pointer to the newly created duplicated string.

3. `_puts` Function:
   - Prints a string (`str`) to the standard output.
   - Iterates through the characters of the string and uses `_putchar` to print each character.
   - This function is used for displaying text.

4. `_putchar` Function:
   - Writes a single character (`c`) to the standard output.
   - It maintains a buffer (`buf`) to accumulate characters and write them to the output in chunks for efficiency.
   - When the buffer is full or a special character (defined as `BUF_FLUSH`) is encountered, it writes the buffered characters to the standard output.
   - Returns the number of characters written, which is always 1.

#20. tokenizer.c file

1. `strtow` Function:
   - Splits a given string (`str`) into words based on a specified delimiter string (`d`).
   - Counts the number of words in the input string by checking for delimiter boundaries.
   - Allocates memory for an array of strings to hold the individual words.
   - Iterates through the input string to extract and store each word in the array.
   - Returns a pointer to the array of strings, or NULL if there's an error.

2. `strtow2` Function:
   - Splits a given string (`str`) into words based on a specified delimiter character (`d`).
   - Counts the number of words in the input string by checking for delimiter boundaries.
   - Allocates memory for an array of strings to hold the individual words.
   - Iterates through the input string to extract and store each word in the array.
   - Returns a pointer to the array of strings, or NULL if there's an error.

#21. vars.c file
Here's a simplified explanation of the provided code:

1. `is_chain` Function:
   - Checks if the current character in a buffer is a chain delimiter (e.g., `||`, `&&`, or `;`).
   - If a chain delimiter is found, it modifies the buffer and updates the `cmd_buf_type` in the `info` structure accordingly.
   - Returns 1 if a chain delimiter is found, otherwise 0.

2. `check_chain` Function:
   - Checks whether chaining should continue based on the last command's exit status and the type of chain delimiter.
   - If the last command used `&&` and its exit status is non-zero, the buffer is modified to skip the remaining commands.
   - If the last command used `||` and its exit status is zero, the buffer is modified to skip the remaining commands.
   - This function adjusts the buffer and position pointers accordingly.

3. `replace_alias` Function:
   - Replaces aliases in the tokenized command with their corresponding values.
   - Iterates through a list of aliases to find a matching alias for the current command.
   - If a match is found, it replaces the command in the `argv` array with the alias value.
   - Returns 1 if an alias is replaced, otherwise 0.

4. `replace_vars` Function:
   - Replaces variables in the tokenized command with their corresponding values.
   - Iterates through the `argv` array to find variables starting with `$`.
   - Handles special variables like `$$` (process ID) and `$?` (exit status).
   - Replaces variables with their values if found.
   - Returns 0 (this function doesn't return 1 as stated in the code comments).

5. `replace_string` Function:
   - Replaces an old string with a new string.
   - Frees the memory occupied by the old string and assigns the new string to the old pointer.
   - Returns 1 if the replacement is successful, otherwise 0.

#22. shell.h file

1. **Header Guards**:
   - The `#ifndef _SHELL_H_` and `#define _SHELL_H_` lines are used to ensure that the header file is included only once in a compilation unit, preventing duplicate definitions.

2. **Include Directives**:
   - This header includes several standard C library headers (`stdio.h`, `stdlib.h`, `string.h`, etc.) and system headers for file I/O, process management, and other system-related functions.

3. **Constants**:
   - Defines several constants used throughout the code, including buffer sizes, command chaining types, and conversion options.

4. **External Environment Variable Declaration**:
   - Declares the external `environ` variable, which is typically used to access environment variables.

5. **Data Structures**:
   - Defines a structure named `liststr` for singly linked lists.
   - Defines a structure named `passinfo` for holding various information related to the shell's state and execution.

6. **Function Prototypes**:
   - Declares prototypes for various functions used in the shell program, such as those for working with linked lists, parsing, error handling, built-in commands, memory management, input/output, and more.

7. **Comments**:
   - Provides comments and descriptions for functions, data structures, and constants to explain their purpose and usage.

Overall, this header file serves as an essential component of the shell program, providing necessary declarations and constants for its functionality. The actual implementation of these functions and structures can be found in the corresponding C source files.
