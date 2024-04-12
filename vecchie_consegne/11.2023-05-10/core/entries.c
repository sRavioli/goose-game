#include "./entries.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

const char *get_name(const Entry *e) { return e->name; }
void set_name(Entry *e, const char *name) {
  snprintf(e->name, MAX_USERNAME_LENGTH + 1, "%s", name);
}

int get_final_score(const Entry *e) { return e->final_score; }
void set_final_score(Entry *e, int final_score) {
  e->final_score = final_score;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

const int get_num_entries(const Entries *es) { return es->num_entries; }
void set_num_entries(Entries *es, const int num_entries) {
  es->num_entries = num_entries;
}

Entry *get_entries(Entries *entries) { return entries->entries; }

const Entry *get_entry(const Entries *es, const int position) {
  return &es->entries[position];
}
void set_entry(Entries *es, Entry *e, const int position) {
  es->entries[position] = *e;
}

//---------------------------------------

void append_entries(Entries *existing_entries, Entries *new_entries) {
  // Copy the new entries to the end of the existing array
  memcpy(get_entries(existing_entries) + get_num_entries(existing_entries),
         get_entries(new_entries),
         get_num_entries(new_entries) * sizeof(Entry));

  // Update the number of entries
  set_num_entries(existing_entries, get_num_entries(existing_entries) +
                                        get_num_entries(new_entries));
}
