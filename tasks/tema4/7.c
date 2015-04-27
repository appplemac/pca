int pointer_read(int *xp) {
  if (xp) xp = *xp;
  return (int)xp;
}
