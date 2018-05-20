#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>

class ConfigEditor : public QWidget
{
  Q_OBJECT
public:
  explicit ConfigEditor(QWidget *parent = nullptr);

signals:

public slots:

private:
  QLineEdit *local_addr_le;
  QLineEdit *local_port_le;
  QLineEdit *remote_addr_le;
  QLineEdit *remote_port_le;

  QLineEdit *passwd_le;
  QCheckBox *append_payload_check;
  QComboBox *log_level_combo;

  QCheckBox *ssl_verify_check;
  QCheckBox *ssl_verify_hostname_check;

  QLineEdit *ssl_cert_path_le;
  QLineEdit *ssl_cipher_le;
  QLineEdit *ssl_server_name_indication_le;
  QLineEdit *ssl_alpn_le;
  QCheckBox *ssl_reuse_session_check;
  QLineEdit *ssl_curves_le;
  QLineEdit *ssl_sig_algorithm_le;






};

#endif // CONFIGEDITOR_H
