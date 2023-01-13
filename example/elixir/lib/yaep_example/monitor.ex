defmodule YaepExample.Monitor do
  use GenServer
  require Logger

  def start_link(_) do
    GenServer.start_link(__MODULE__, %{}, name: __MODULE__)
  end

  # Callbacks

  @impl true
  def init(state) do
    Logger.info "Starting node connection monitor..."
    :ok = :net_kernel.monitor_nodes(true, node_type: :hidden)
    {:ok, state}
  end

  @impl true
  def handle_info({status, node, _opts} = msg, state) when is_atom(node) do
    Logger.info "Status update: #{inspect(msg)}"
    if status == :nodeup do
      Logger.info "Sending handshake message to registed process 'php' at node '#{node}'"
      send({:php, node}, {self(), "Handshake!"})
    end
    {:noreply, state}
  end

  def handle_info({:ping, from, _bin} = misc_msg, state) when is_pid(from) do
    Logger.info "Received ping message: #{inspect(misc_msg)}"
    send(from, :pong)
    {:noreply, state}
  end

  def handle_info(misc_msg, state) do
    Logger.info "Received unexpected message: #{inspect(misc_msg)}"
    {:noreply, state}
  end
end
