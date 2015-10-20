//
// SslEngine.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Oct 20 14:35:59 2015 chapui_s
// Last update Tue Oct 20 14:35:59 2015 chapui_s
//

#ifndef SSLENGINE_H_
# define SSLENGINE_H_

# include "ISocketEngine.hh"

class		SslEngine : public ISocketEngine
{
private:
  SslSocket	_socket;
  bool		_error;

  void		checkHandshake(const boost::system::error_code &, const std::function<void()> &);
  void		checkRead(const boost::system::error_code &, const std::function<void()> &);
  void		checkWrite(const boost::system::error_code &, const std::function<void()> &);
  void		checkReadSome(const boost::system::error_code &, const std::function<void()> &);
  void		checkWriteSome(const boost::system::error_code &, const std::function<void()> &);

public:
  SslEngine(boost::asio::io_service &, boost::asio::ssl::context &);
  virtual ~SslEngine();

  virtual bool	isConnected() const;
  virtual SslSocket::lowest_layer_type	&getSocket();
  virtual void			doHandshake(boost::asio::ssl::stream_base::handshake_type,
					    const std::function<void()> &);
  virtual void			async_read(void *, size_t, const std::function<void()> &);
  virtual void			async_write(void *, size_t, const std::function<void()> &);
  virtual void			async_read_some(void *, size_t, const std::function<void()> &);
  virtual void			async_write_some(void *, size_t, const std::function<void()> &);
};


#endif /* !SSLENGINE_H_ */
