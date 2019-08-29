/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "locale/TranslatableConfiguration.h"
#include "utils/NamedEnum.h"

#include <QAbstractListModel>
#include <QObject>
#include <QPixmap>
#include <QVector>

enum class PackageChooserMode
{
    Optional,  // zero or one
    Required,  // exactly one
    OptionalMultiple,  // zero or more
    RequiredMultiple  // one or more
};

const NamedEnumTable< PackageChooserMode >& roleNames();

struct PackageItem
{
    QString id;
    // FIXME: unused
    QString package;
    CalamaresUtils::Locale::TranslatedString name;
    CalamaresUtils::Locale::TranslatedString description;
    QPixmap screenshot;

    /// @brief Create blank PackageItem
    PackageItem();
    /** @brief Creates a PackageItem from given strings
     *
     * This constructor sets all the text members,
     * but leaves the screenshot blank. Set that separately.
     */
    PackageItem( const QString& id, const QString& package, const QString& name, const QString& description );

    /** @brief Creates a PackageItem from given strings.
     *
     * Set all the text members and load the screenshot from the given
     * @p screenshotPath, which may be a QRC path (:/path/in/qrc) or
     * a filesystem path, whatever QPixmap understands.
     */
    PackageItem( const QString& id,
                 const QString& package,
                 const QString& name,
                 const QString& description,
                 const QString& screenshotPath );

    /** @brief Creates a PackageItem from a QVariantMap
     *
     * This is intended for use when loading PackageItems from a
     * configuration map. It will look up the various keys in the map
     * and handle translation strings as well.
     */
    PackageItem( const QVariantMap& map );

    /** @brief Is this item valid?
     *
     * A valid item has an untranslated name available.
     */
    bool isValid() const { return !name.isEmpty(); }

    /** @brief Loads an AppData XML file and returns a PackageItem
     *
     * The @p map must have a key *appdata*. That is used as the
     * primary source of information, but keys *id* and *screenshotPath*
     * may be used to override parts of the AppData -- so that the
     * ID is under the control of Calamares, and the screenshot can be
     * forced to a local path available on the installation medium.
     *
     * Requires XML support in libcalamares, if not present will
     * return invalid PackageItems.
     */
    static PackageItem fromAppData( const QVariantMap& map );
};

using PackageList = QVector< PackageItem >;

class PackageListModel : public QAbstractListModel
{
public:
    PackageListModel( PackageList&& items, QObject* parent );
    PackageListModel( QObject* parent );
    virtual ~PackageListModel() override;

    /** @brief Add a package @p to the model
     *
     * Only valid packages are added -- that is, they must have a name.
     */
    void addPackage( PackageItem&& p );

    int rowCount( const QModelIndex& index ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    enum Roles : int
    {
        NameRole = Qt::DisplayRole,
        DescriptionRole = Qt::UserRole,
        ScreenshotRole,
        IdRole
    };

private:
    PackageList m_packages;
};

#endif
