//implement int strlen()
int myStrlen(const char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++)
    {
      ;
    }
  return i;
}

//implenting strcpy (dest,source)
void myStrcpy( char dest[], const char source[])
{
  int i;
  for (i = 0; source[i] != '\0'; i++)
    {
      dest[i] = source[i];
    }
  dest[i] = '\0';
}


//implementing toUpper()
char myToUpper(char c)
{
  if(c >= 'a' && c <= 'z')
    c = c-32;

  return c;
}
