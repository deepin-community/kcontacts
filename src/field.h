/*
    This file is part of the KContacts framework.
    SPDX-FileCopyrightText: 2002 Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KCONTACTS_FIELD_H
#define KCONTACTS_FIELD_H

#include "kcontacts_export.h"

#if KCONTACTS_ENABLE_DEPRECATED_SINCE(5, 88)
#include "addressee.h"
#include <QString>

class KConfigGroup;

namespace KContacts
{
/**
 * @short Represents a field in the Addressbook
 *
 * This class represents a field in the Addressbook database.
 * It provides methods for accessing meta-information about
 * the field (such as label() or category()) as well as
 * getting or setting the field's value in an instance of
 * Addressee (value(), setValue()).
 *
 * Furthermore, some static methods are provided for getting
 * a list of all fields (allFields(), defaultFields()), for
 * creating new fields (createCustomField()) and for saving
 * or loading fields to/from a config file (saveFields(),
 * restoreFields()).
 *
 * @deprecated since 5.88, class is unused
 */
class KCONTACTS_EXPORT KCONTACTS_DEPRECATED_VERSION(5, 88, "class is unused") Field
{
public:
    /**
     * This type is used for a list of fields.
     */
    typedef QList<Field *> List;

    /**
     * Represents the category a field belongs to.
     */
    enum FieldCategory {
        /**
         * All fields
         */
        All = 0x0,
        /**
         * Frequently used fields
         */
        Frequent = 0x01,
        /**
         * Fields which belong to the address, such as Street, City, Zip, etc.
         */
        Address = 0x02,
        /**
         * Fields which store information about the e-mail contact, such as
         * e-mail address or mail client
         */
        Email = 0x04,
        /**
         * Personal fields, such as Birthday, Home Address fields, IM Address, etc.
         */
        Personal = 0x08,
        /**
         * Fields about the organization, such as Business Address fields, Department,
         * Profession, etc.
         */
        Organization = 0x10,
        /**
         * Custom (user-defined) fields
         */
        CustomCategory = 0x20,
    };

    /**
     * Returns the translated label for this field.
     */
    Q_REQUIRED_RESULT virtual QString label();

    /**
     * Returns the  ored categories the field belongs to.
     */
    Q_REQUIRED_RESULT virtual int category();

    /**
     * Returns the translated label for @p category.
     *
     * @param category the category of type FieldCategory
     * @return the translated label
     */
    static QString categoryLabel(int category);

    /**
     * Returns a string representation of the value the field has in the given
     * Addressee.
     *
     * @return the string representation of the value or QString(), if it
     * is not possible to convert the value to a string.
     */
    Q_REQUIRED_RESULT virtual QString value(const KContacts::Addressee &addressee);

    /**
     * Sets the value of the field in the given Addressee.
     *
     * @return @c true on success or @c false, if the given string couldn't
     * be converted to a valid value.
     */
    Q_REQUIRED_RESULT virtual bool setValue(KContacts::Addressee &addressee, const QString &value);

    /**
     * Returns a string, that can be used for sorting.
     */
    Q_REQUIRED_RESULT QString sortKey(const KContacts::Addressee &addressee);

    /**
     * Returns, if the field is a user-defined field.
     *
     * @return @c true if this is a custom field, @c false otherwise
     */
    Q_REQUIRED_RESULT virtual bool isCustom();

    /**
     * Returns, if the field is equal with @p field.
     *
     * @param field the field to compare this field to
     * @return @c true if the fields are equal, @c false otherwise
     */
    Q_REQUIRED_RESULT virtual bool equals(Field *field);

    /**
     * Returns a list of all fields.
     */
    static Field::List allFields();

    /**
     * Returns a list of the default fields.
     */
    Q_REQUIRED_RESULT static Field::List defaultFields();

    /**
     * Creates a custom field.
     *
     * @param label    The label for this field
     * @param category The category of this field
     * @param key      Unique key for this field
     * @param app      Unique app name for this field
     */
    static Field *createCustomField(const QString &label, int category, const QString &key, const QString &app);

    /**
     * Delete all fields from list.
     */
    static void deleteFields();

    /**
     * Save the field settings to a config file.
     *
     * @param cfg        The config file object
     * @param identifier The unique identifier
     * @param fields     The list of the fields
     */
    static void saveFields(KConfigGroup &cfg, const QString &identifier, const Field::List &fields);
    /**
     * @overload
     *
     * Here, the list is stored in KSharedConfig::openConfig() in group "KABCFields".
     *
     * @param identifier The unique identifier
     * @param fields     The list of the fields
     */
    static void saveFields(const QString &identifier, const Field::List &fields);

    /**
     * Load the field settings from a config file.
     *
     * @param cfg        The config file object
     * @param identifier The unique identifier
     */
    static Field::List restoreFields(const KConfigGroup &cfg, const QString &identifier);

    /**
     * @overload
     *
     * Here, the list is loaded from KSharedConfig::openConfig() from group "KABCFields".
     *
     * @param identifier The unique identifier
     */
    static Field::List restoreFields(const QString &identifier);

protected:
    /**
     * @internal
     *
     * Creates a field and appends it to the general list of fields.
     *
     * @param id The identifier for the field
     * @param category The optional category for the field
     */
    static void createField(int id, int category = 0);

    /**
     * @internal
     *
     * Creates a field and appends it to the list of default fields.
     *
     * @param id The identifier for the field
     * @param category The optional category for the field
     */
    static void createDefaultField(int id, int category = 0);

private:
    class Private;

    Field(Private *p);
    virtual ~Field();

    Private *const d;
};
}
#endif
#endif
