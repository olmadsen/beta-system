

CharPosToRowCol (char *value, long pos, long *row, long *col)
{
  long i = 0;
  (*col) = 0;
  (*row) = 0;
  while (i < pos) {
    if (value[i] == '\n') {
      (*row)++;
      (*col) = 0;
    }
    else {
      (*col)++;
    }
    i++;
  }
}

CharRowColToPos (char *value, long row, long col, long *pos)
{
  long line = 0;
  while (line < row) {
    if (value[*pos] == '\n') {
      line++;
    }
    (*pos)++;
  }
  (*pos) += col;
}
