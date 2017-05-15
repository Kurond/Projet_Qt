#ifndef CONSULT_H
#define CONSULT_H


class Consult
{
public:
    Consult();
    Consult(int id, int idPatient, int idRessource);

    int _id;
    int _idPatient;
    int _idRessource;
};

#endif // CONSULT_H
