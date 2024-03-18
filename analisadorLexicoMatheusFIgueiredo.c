#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keyword[32][32] =
{
  "auto", "const", "double", "float", "int", "short", "struct", "unsigned",
  "break", "continue", "else", "for", "long", "signed", "switch", "void",
  "case", "default", "enum", "goto", "register", "sizeof", "typedef",
  "volatile", "char", "do", "extern", "if", "return", "static", "union",
  "while"
};

char id[20], num[10];

int check_keyword (char s[])
{
  int i;
  for (i = 0; i < 32; i++)
  {
    if (strcmp (s, keyword[i]) == 0)
      return 1;
  }
  return 0;
}

int main()
{
  FILE *fp1, *fp2;
  char c;
  int state = 0;
  int i = 0, j = 0;

  fp1 = fopen("H:\\compiladores\\input.txt", "r");
  fp2 = fopen("H:\\compiladores\\output.txt", "w");

  if (fp1 == NULL || fp2 == NULL)
  {
    printf("Erro ao abrir os arquivos\n");
    return 1;
  }

  while ((c = fgetc(fp1)) != EOF)
  {
    switch (state)
    {
      case 0:
        if (isalpha(c) || c == '-')
        {
          state = 1;
          id[i++] = c;
        }
        else if (isdigit(c))
        {
          state = 3;
          num[j++] = c;
        }
        else if (c == '<' || c == '>')
        {
          state = 5;
        }
        else if (c == '=' || c == '!')
        {
          state = 8;
        }
        else if (c == '/')
        {
          state = 10;
        }
        else if (c == ' ' || c == '\t' || c == '\n')
        {
          state = 0;
        }
        else
        {
          fprintf(fp2, "\n%c", c);
          break;
        }
        break;

      case 1:
        if (isalnum(c))
        {
          state = 1;
          id[i++] = c;
        }
        else
        {
          id[i] = '\0';
          if (check_keyword(id))
          {
            fprintf(fp2, "\n%s : keyword", id);
          }
          else
          {
            fprintf(fp2, "\n%s : identifier", id);
          }
          state = 0;
          i = 0;
          ungetc(c, fp1);
        }
        break;

      case 3:
        if (isdigit(c))
        {
          num[j++] = c;
          state = 3;
        }
        else
        {
          num[j] = '\0';
          fprintf(fp2, "\n%s : number", num);
          state = 0;
          j = 0;
          ungetc(c, fp1);
        }
        break;

      case 5:
        if (c == '=')
        {
          fprintf(fp2, "\nrelational operator");
          state = 0;
        }
        else
        {
          fprintf(fp2, "\nrelational operator");
          state = 0;
          ungetc(c, fp1);
        }
        break;

      case 8:
    if (c == '=') {
        fprintf(fp2, "\n relational operator");
        state = 0;
    } else {
        fprintf(fp2, "\n !");
        state = 0;
        ungetc(c, fp1);
    }
    break;

case 10:
    if (c != '*') {
        state = 11;
    } else {
        state = 13;
    }
    break;

case 11:
    if (c != '*' && c != '/') {
        state = 11;
    } else if (c == '*') {
        state = 12;
    } else {
        state = 0;
        ungetc(c, fp1);
    }
    break;

case 12:
    if (c == '*') {
        state = 12;
    } else if (c == '/') {
        state = 0;
    } else {
        state = 11;
    }
    break;

case 13:
    if (c == '*') {
        state = 14;
    } else {
        state = 13;
    }
    break;

case 14:
    if (c == '*') {
        state = 14;
    } else if (c == '/') {
        state = 0;
    } else {
        state = 13;
    }
    break;
	} //end of switch
} //end of while

    fclose(fp1);
    fclose(fp2);
    printf("Análise léxica finalizada.");

    return 0;
}
