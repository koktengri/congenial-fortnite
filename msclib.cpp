#include "msclib.hpp"

/* /////////////////////////////////////////////////
 * /////////////Implementation of Note//////////////
 * /////////////////////////////////////////////////
 */

namespace msc {

Note & Note::operator=(const Note& note) {
    val = note.val;
    octave = note.octave;
    return *this;
}

Note& Note::operator+=(const Interval& interval) {
    octave += (val + interval.val) / 12 + interval.octaves;
    val = (note_val)((val + interval.val) % 12);
    return *this;
}

Note& Note::operator-=(const Interval& interval) {
    octave += (val - interval.val) / 12 - 1;
    val = (note_val)((val - interval.val) % 12);
    return *this;
}

Note Note::operator+(const Interval& interval) const {
    return Note((note_val)(val + interval.val));
}

Interval Note::operator-(const Note& note) const {
    return Interval((interval_val)(val - note.val));
}

bool Note::operator==(const Note& note) const {
    return val == note.val && octave == note.octave;
}

bool Note::operator!=(const Note& note) const {
    return !(this == note);
}

/* /////////////////////////////////////////////////
 * //////////Implementation of Interval/////////////
 * /////////////////////////////////////////////////
 */

Interval::Interval(const interval_val v) {
    val = (interval_val)(v % 12);
}

Interval& Interval::operator=(const Interval& interval) {
    val = interval.val;
    return *this;
}

/*Interval& Interval::operator=(const interval_val v) {
    val = v;
    return *this;
}*/

Interval& Interval::operator+=(const Interval& interval) {
    val = (interval_val)((val + interval.val) % 12);
    return *this;
}

Interval& Interval::operator-=(const Interval& interval) {
    val = (interval_val)((val - interval.val) % 12);
    return *this;
}

Interval Interval::operator+(const Interval& interval) const {
    return Interval((interval_val)(val + interval.val));
}

Interval Interval::operator-(const Interval& interval) const {
    return Interval((interval_val)(val - interval.val));
}

bool Interval::operator==(const Interval& interval) const {
    return val == interval.val;
}

bool Interval::operator!=(const Interval& interval) const {
    return !(this == interval);
}
}

/*

measure * init_measure(Note key, time_sig meter, int voices) {
    Note ** notes = malloc(sizeof(Note*) * voices);
    for (i = 0; i < voices; i++) notes[i] = malloc(sizeof(Note) * meter.beats);
    measure m = malloc(sizeof(measure));
    m = {.key = key, .meter = meter, .voices = voices, .notes = notes};
    return &measure;
}

void delete_measure(measure * m) {
    for (i = 0; i < m.voices; i++) free(m.notes[i]);
    free(m.notes);
    free(m.meter);
    free(m);
}
*/