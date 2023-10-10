#include "custom_shell.h"

int custom_alias(char **args, char __attribute__((__unused__)) **head);
void set_custom_alias(char *alias_name, char *alias_value);
void print_custom_alias(alias_t *alias);

/**
 * custom_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @head: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int custom_alias(char **args, char __attribute__((__unused__)) **head)
{
	alias_t *alias_temp = aliases;
	int i, ret = 0;
	char *alias_value;

	if (!args[0])
	{
		while (alias_temp)
		{
			print_custom_alias(alias_temp);
			alias_temp = alias_temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		alias_temp = aliases;
		alias_value = _strchr(args[i], '=');
		if (!alias_value)
		{
			while (alias_temp)
			{
				if (_strcmp(args[i], alias_temp->name) == 0)
				{
					print_custom_alias(alias_temp);
					break;
				}
				alias_temp = alias_temp->next;
			}
			if (!alias_temp)
				ret = create_error(args + i, 1);
		}
		else
			set_custom_alias(args[i], alias_value);
	}
	return (ret);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new alias_name,
 * 'alias_name' or creates a new alias with 'name' and 'alias_value'.
 * @alias_name: Name of the alias.
 * @alias_value: value of the alias. First character is a '='.
 */
void set_custom_alias(char *alias_name, char *alias_value)
{
	alias_t *alias_temp = aliases;
	int len, j, z = 0;
	char *new_alias_value;

	*alias_value = '\0';
	alias_value++;
	len = _strlen(alias_value) - _strspn(alias_value, "'\"");
	new_alias_value = malloc(sizeof(char) * (len + 1));
	if (!new_alias_value)
		return;
	for (j = 0; alias_value[j]; j++)
	{
		if (alias_value[j] != '\'' && alias_value[j] != '"')
			new_alias_value[z++] = alias_value[j];
	}
	new_alias_value[z] = '\0';
	while (alias_temp)
	{
		if (_strcmp(alias_name, alias_temp->name) == 0)
		{
			free(alias_temp->alias_value);
			alias_temp->alias_value = new_alias_value;
			break;
		}
		alias_temp = alias_temp->next;
	}
	if (!alias_temp)
		add_alias_end(&aliases, alias_name, new_alias_value);
}

/**
 * print_custom_alias - Prints the alias in the format name='alias_value'.
 * @alias: Pointer to an alias.
 */
void print_custom_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->alias_value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->alias_value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their alias_name.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *alias_temp;
	int i;
	char *new_alias_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		alias_temp = aliases;
		while (alias_temp)
		{
			if (_strcmp(args[i], alias_temp->name) == 0)
			{
				new_alias_value = malloc(sizeof(char) * (_strlen(alias_temp->alias_value) + 1));
				if (!new_alias_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_alias_value, alias_temp->alias_name);
				free(args[i]);
				args[i] = new_alias_value;
				i--;
				break;
			}
			alias_temp = alias_temp->next;
		}
	}

	return (args);
}
