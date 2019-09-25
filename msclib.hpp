#ifndef MSCLIB_H
#define MSCLIB_H

/*
 *  msclib.hpp      ---- music representation library ----
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define s_deg int       // the scale degree 1-7
#define Brightness int  // the brightness of a mode -3 to 3

namespace msc {

    enum class note_v : int {
        Bs = 0,  //belongs to previous octave
        C  = 0,
        Cs = 1,
        Df = 1,
        D  = 2,
        Ds = 3,
        Ef = 3,
        E  = 4,
        Es = 5,
        Ff = 4,
        F  = 5,
        Fs = 6,
        Gf = 6,
        G  = 7,
        Gs = 8,
        Af = 8,
        A  = 9,
        As = 10,
        Bf = 10,
        B  = 11,
        Cf = 11  //belongs to next octave
    };

    enum class int_v : int {
        uni = 0,
        d2  = 0,
        m2  = 1,
        M2  = 2,
        A2  = 3,
        d3  = 2,
        m3  = 3,
        M3  = 4,
        A3  = 5,
        d4  = 4,
        P4  = 5,
        A4  = 6,
        d5  = 6,
        P5  = 7,
        A5  = 8,
        d6  = 7,
        m6  = 8,
        M6  = 9,
        A6  = 10,
        d7  = 9,
        m7  = 10,
        M7  = 11,
        A7  = 0,
        oct = 0
    };

    class Interval;
    class Chord;
    struct Roman;

    // wrapper for note
    class Note {
       public:
        note_v val;
        short octaves;  // negative if note is a rest (represents which octave 0-8)

        //constructor
        Note(const note_v val = note_v::C, const short octaves = 4)
            : octaves(octaves), val(val) {}
        //destructor
        ~Note() = default;
        //copy constructor
        Note(const Note & other) = default;
        //copy assign
        Note & operator=(const Note & other) = default;
        //move constructor
        Note(Note && other) = default;
        //move assign
        Note & operator=(Note && other) = default;

        Note & operator++();  // increments value by half step

        Note & operator--();  // decrements value by half step

        Note & operator+=(const Interval & interval);

        Note & operator-=(const Interval & interval);

        Note operator+(const Interval & interval) const;

        Chord operator+(const Note & third) const;  // returns a chord with the note as the root with the third, may be inverted. returns null if chord not constructible

        Interval operator-(const Note & note) const;  //interval between the two notes, nonnegative

        bool operator==(const Note & note) const;

        bool operator!=(const Note & note) const;

        bool operator<(const Note & note) const;  //ordered lowest to highest in pitch

        bool operator>(const Note & note) const;

        bool operator<=(const Note & note) const;

        bool operator>=(const Note & note) const;
    };

    // all 97 notes C0 - C8 including sharps and flats
    namespace Notes {
        const Note
            C0{C, 0},
            Cs0{Cs, 0},
            Df0{Df, 0},
            D0{D, 0},
            Ds0{Ds, 0},
            Ef0{Ef, 0},
            E0{E, 0},
            Es0{Es, 0},
            Ff0{Ff, 0},
            F0{F, 0},
            Fs0{Fs, 0},
            Gf0{Gf, 0},
            G0{G, 0},
            Gs0{Gs, 0},
            Af0{Af, 0},
            A0{A, 0},
            As0{As, 0},
            Bf0{Bf, 0},
            B0{B, 0},
            Cf1{Cf, 0},
            Bs0{Bs, 1},
            C1{C, 1},
            Cs1{Cs, 1},
            Df1{Df, 1},
            D1{D, 1},
            Ds1{Ds, 1},
            Ef1{Ef, 1},
            E1{E, 1},
            Es1{Es, 1},
            Ff1{Ff, 1},
            F1{F, 1},
            Fs1{Fs, 1},
            Gf1{Gf, 1},
            G1{G, 1},
            Gs1{Gs, 1},
            Af1{Af, 1},
            A1{A, 1},
            As1{As, 1},
            Bf1{Bf, 1},
            B1{B, 1},
            Cf2{Cf, 1},
            Bs1{Bs, 2},
            C2{C, 2},
            Cs2{Cs, 2},
            Df2{Df, 2},
            D2{D, 2},
            Ds2{Ds, 2},
            Ef2{Ef, 2},
            E2{E, 2},
            Es2{Es, 2},
            Ff2{Ff, 2},
            F2{F, 2},
            Fs2{Fs, 2},
            Gf2{Gf, 2},
            G2{G, 2},
            Gs2{Gs, 2},
            Af2{Af, 2},
            A2{A, 2},
            As2{As, 2},
            Bf2{Bf, 2},
            B2{B, 2},
            Cf3{Cf, 2},
            Bs2{Bs, 3},
            C3{C, 3},
            Cs3{Cs, 3},
            Df3{Df, 3},
            D3{D, 3},
            Ds3{Ds, 3},
            Ef3{Ef, 3},
            E3{E, 3},
            Es3{Es, 3},
            Ff3{Ff, 3},
            F3{F, 3},
            Fs3{Fs, 3},
            Gf3{Gf, 3},
            G3{G, 3},
            Gs3{Gs, 3},
            Af3{Af, 3},
            A3{A, 3},
            As3{As, 3},
            Bf3{Bf, 3},
            B3{B, 3},
            Cf4{Cf, 3},
            Bs3{Bs, 4},
            C4{C, 4},
            Cs4{Cs, 4},
            Df4{Df, 4},
            D4{D, 4},
            Ds4{Ds, 4},
            Ef4{Ef, 4},
            E4{E, 4},
            Es4{Es, 4},
            Ff4{Ff, 4},
            F4{F, 4},
            Fs4{Fs, 4},
            Gf4{Gf, 4},
            G4{G, 4},
            Gs4{Gs, 4},
            Af4{Af, 4},
            A4{A, 4},
            As4{As, 4},
            Bf4{Bf, 4},
            B4{B, 4},
            Cf5{Cf, 4},
            Bs4{Bs, 5},
            C5{C, 5},
            Cs5{Cs, 5},
            Df5{Df, 5},
            D5{D, 5},
            Ds5{Ds, 5},
            Ef5{Ef, 5},
            E5{E, 5},
            Es5{Es, 5},
            Ff5{Ff, 5},
            F5{F, 5},
            Fs5{Fs, 5},
            Gf5{Gf, 5},
            G5{G, 5},
            Gs5{Gs, 5},
            Af5{Af, 5},
            A5{A, 5},
            As5{As, 5},
            Bf5{Bf, 5},
            B5{B, 5},
            Cf6{Cf, 5},
            Bs5{Bs, 6},
            C6{C, 6},
            Cs6{Cs, 6},
            Df6{Df, 6},
            D6{D, 6},
            Ds6{Ds, 6},
            Ef6{Ef, 6},
            E6{E, 6},
            Es6{Es, 6},
            Ff6{Ff, 6},
            F6{F, 6},
            Fs6{Fs, 6},
            Gf6{Gf, 6},
            G6{G, 6},
            Gs6{Gs, 6},
            Af6{Af, 6},
            A6{A, 6},
            As6{As, 6},
            Bf6{Bf, 6},
            B6{B, 6},
            Cf7{Cf, 6},
            Bs6{Bs, 7},
            C7{C, 7},
            Cs7{Cs, 7},
            Df7{Df, 7},
            D7{D, 7},
            Ds7{Ds, 7},
            Ef7{Ef, 7},
            E7{E, 7},
            Es7{Es, 7},
            Ff7{Ff, 7},
            F7{F, 7},
            Fs7{Fs, 7},
            Gf7{Gf, 7},
            G7{G, 7},
            Gs7{Gs, 7},
            Af7{Af, 7},
            A7{A, 7},
            As7{As, 7},
            Bf7{Bf, 7},
            B7{B, 7},
            Cf8{Cf, 7},
            Bs7{Bs, 8},
            C8{C, 8};

    };  // namespace Notes

    // wrapper for interval
    class Interval {
       public:
        int_v val;
        short octaves = 0;  // number of octaves in the interval, must be nonnegative

        //constructor
        Interval(const int_v val = int_v::uni, const int octaves = 0)
            : val(val), octaves(octaves) {}
        //destructor
        ~Interval() = default;
        //copy constructor
        Interval(const Interval & other) = default;
        //copy assign
        Interval & operator=(const Interval & other) = default;
        //move constructor
        Interval(Interval && other) = default;
        //move assign
        Interval & operator=(Interval && other) = default;

        Interval & operator++();  // increments interval by half step

        Interval & operator--();  // decrements interval by half step

        Interval & operator+=(const Interval & interval);

        Interval & operator-=(const Interval & interval);  //if subtracted interval is greater, the original interval becomes their difference

        Interval operator+(const Interval & interval) const;

        Interval operator-(const Interval & interval) const;

        bool operator==(const Interval & interval) const;

        bool operator!=(const Interval & interval) const;

        bool operator<(const Note & interval) const;  //ordered according to size of interval

        bool operator>(const Note & interval) const;

        bool operator<=(const Note & interval) const;

        bool operator>=(const Note & interval) const;
    };

    // common intervals Uni-Oct
    namespace Intervals {
        const Interval uni{uni}, d2{d2}, m2{m2}, M2{M2}, A2{A2}, d3{d3}, m3{m3}, M3{M3},
            A3{A3}, d4{d4}, P4{P4}, A4{A4}, d5{d5}, P5{P5}, A5{A5}, d6{d6}, m6{m6},
            M6{M6}, A6{A6}, d7{d7}, m7{m7}, M7{M7}, A7{A7}, oct{oct};
    }

    //functional heptatonic scale, doesn't specify root note
    struct Scale {
        Interval Supertonic;
        Interval Mediant;
        Interval Subdominant;
        Interval Dominant;
        Interval Submediant;
        Interval Subtonic;  // or leading tone

        Scale();  //initializes Ionian scale

        Scale(Interval * intervals);  //construct scale from Interval[7] (strictly increasing order, less than oct)

        //construct scale from Interval[7] (strictly increasing order, less than oct)
        Scale(Interval SuperTonic, Interval Mediant, Interval Subdominant, Interval Dominant, Interval Submediant, Interval Subtonic)
            : Supertonic(Supertonic), Mediant(Mediant), Subdominant(Subdominant), Dominant(Dominant), Submediant(Submediant), Subtonic(Subtonic) {}

        Scale(Roman tonic, Roman dominant, Roman subdominant);  //construct scale from Roman[3] (tonic, dominant, subdominant)

        Scale(Chord tonic, Chord dominant, Chord subdominant);  //construct scale from Chord[3] (tonic, dominant, subdominant)

        ~Scale() = default;

        bool operator==(const Scale & other) const;  // true if all intervals are same
        bool operator!=(const Scale & other) const;

        /*comparison is defined on the sum of the values of the intervals,
         * this preserves order of brightness for modes*/
        bool operator<(const Scale & other) const;
        bool operator>(const Scale & other) const;
        bool operator<=(const Scale & other) const;
        bool operator>=(const Scale & other) const;

        // returns a roman that has the root at scale degree s_root
        Roman chords_of_scale(int s_root) const;
    };

    struct Mode : public Scale {
        //to be called only with valid intervals: internal functionality to check whether the input is a valid mode would be a nice future addition
        Mode(Interval Supertonic, Interval Mediant, Interval Subdominant, Interval Dominant, Interval Submediant, Interval Subtonic)
            : Scale(Supertonic, Mediant, Subdominant, Dominant, Submediant, Subtonic) {}

        Mode(Brightness br);  //constructs mode from level of brightness

        Brightness mode_to_br(Scale mode);  // returns the brightness of the mode from 0-6, 0 darkest, 6 brightest

        Mode & operator++();  // brightens mode by single sharp

        Mode & operator--();  // darkens mode by single flat

        Mode & operator+=(int incr);  //brightens mode by incr sharps

        Mode & operator-=(int decr);  //brightens mode by decr flats

        Mode operator+(int incr);  //returns mode brightened by incr sharps

        Mode operator-(int decr);  //returns mode brightened by decr flats
    };

    namespace Modes {
        const Mode
            Ionian{M2, M3, P4, P5, M6, M7},
            Dorian{M2, m3, P4, P5, M6, m7},
            Phrygian{m2, m3, P4, P5, m6, m7},
            Lydian{M2, M3, A4, P5, M6, M7},
            Mixolydian{M2, M3, P4, P5, M6, m7},
            Aeolian{M2, m3, P4, P5, m6, m7},
            Locrian{m2, m3, P4, m5, m6, m7};
    }

    namespace Common_Scales {
        const Scale Maj = {M2, M3, P4, P5, M6, M7},
                    Ntr_min{M2, m3, P4, P5, m6, m7},
                    Hrm_min = {M2, m3, P4, P5, m6, M7},
                    Mld_min = {M2, m3, P4, P5, M6, M7};
    }

    enum class chord_type : int {
        Maj,  //Major triad˝
        min,  //minor triad
        Aug,  //Augmented triad
        dim,  //diminished triad
        MM7,  //Major triad + Major 7th (Major-Major 7)
        D7,   //Major triad + minor 7th (Major-minor 7)
        mM7,  // minor triad + Major 7th (minor-Major 7)
        m7,   //minor triad + minor 7th (minor 7)
        A7,   //Augmented triad + minor 7th (Augmented 7)
        AM7,  //Augmented triad + Major 7th (Augmented-Major 7)
        d7,   //diminished triad + diminished 7th (diminished 7)
        hd7   //diminished triad + minor 7th (half-diminished 7)
    };

    /*returns the third, fifth, and seventh (if exists otherwise unison) (respectively interval_num = 3, 5, or 7)*/
    Interval ioct(chord_type type, int interval_num);  //(i)ntervals(o)f(c)hord(t)ype

    // wrapper to combine the root scale degree of chord and its type, e.g. a V7 chord is {5, D7}
    class Roman {
       public:
        s_deg root      = 0;    // scale degree of root of chord, 0 indicates null chord
        chord_type func = Maj;  // functionality of chord
                                // Note:the secondary dominant to a chord will be created by creating a
                                // scale from the base chord
        Roman() : root(0), func(Maj) {}

        Roman(s_deg root, chord_type func) : root(root), func(func) {}

        Roman(Scale scale, s_deg root);  // root 1-7 represents scale degree of root of chord

        Interval third() const;
        Interval fifth() const;
        Interval seventh() const;  //returns unison if no seventh
    };

    // harmonic functionality ***NOTE: The graph algorithms will use these harmonic
    // functions as vertices***
    namespace Common_Roman {
        const Roman
            // major
            I    = {1, Maj},
            ii   = {2, min},
            iii  = {3, min},
            IV   = {4, Maj},
            V    = {5, Maj},
            vi   = {6, min},
            viio = {7, dim},
            // minor chords not in major
            i   = {1, min},
            iio = {2, dim},
            III = {3, Maj},
            iv  = {4, min},
            v   = {5, min},
            VI  = {6, Maj},
            VII = {7, Maj};
        /*FUTURE ADDITIONS: 7th chords, for now 7ths are nonchord tones*/
        /*FUTURE ADDITIONS: N, It6, Fr6, Ger6 (Neapolitan and augmented 6th chords) */
    }  // namespace Common_Roman

    //represents an actual chord that has known positions for each of its notes, only to be used to generate voice-leading
    class Chord : public Roman {
        /**** TODO ****/
    };

    struct Meter {
        int beats    = 4;  // beats per measure
        int beat_val = 4;  // inverted, a 4 is a quarter note
    };

    // note: melodies are functionally represented as s_deg* and are 0-terminated

    // harmonic functional abstraction of a measure, includes a single chord for the
    // entire measure and a melody with one note per beat
    struct Measure_f {
        Meter meter;
        std::vector<s_deg> * melody;  // has as many notes as meter.beats, represented as scale degrees
        Roman chord = Common_Roman::I;

        Measure_f(const Meter & meter);

        Measure_f(const Meter & meter, const Roman & chord);

        Measure_f(const Meter & other_m, const Roman & chord, const std::vector<s_deg> & mel);

        Measure_f(Meter & other_m, s_deg * mel);

        ~Measure_f() { delete melody; }
    };

    //TODO: an actual measure complete with notes
    struct Measure : Measure_f {
        int voices = 4;
        /**** TODO ****/
    };

    /*struct representing only the melodic line and associated chords for a section of the piece*/
    struct Section_f {
        Meter meter;  //meter of first measure of section
        Scale scale;
        std::vector<Measure_f> measures;
    };

    /*class representing (section of) a piece*/
    class Section : Section_f {
        Note key;
        int voices = 4;
        /*the key, meter, and number of voices of the section should be the same for each measure*/
        std::vector<Measure_f> measures;

       public:
        Section(Note key = Notes::C4, Meter meter = {4, 4}, int voices = 4, int length = 1);

        ~Section();
    };

    class Piece_f {
       public:
        std::vector<Section_f> sections;
    };

    class Piece : Piece_f {
        /**** TODO ****/
    };

}  // namespace msc

#endif
